#pragma once

#include "di/container/intrusive/atomic_batch_queue.h"
#include "di/execution/coroutine/lazy.h"
#include "di/execution/interface/schedule.h"
#include "di/execution/interface/timed_scheduler.h"
#include "di/execution/macro/co_try.h"
#include "di/execution/receiver/prelude.h"
#include "di/execution/types/completion_signuatures.h"
#include "di/execution/util/resource_helper.h"
#include "di/execution/util/variant_sender.h"
#include "di/function/make_deferred.h"
#include "dius/io.h"
#include "dius/linux/epoll.h"
#include "dius/linux/eventfd.h"
#include "dius/linux/inotify.h"
#include "dius/linux/signalfd.h"
#include "dius/net/address.h"
#include "dius/net/socket.h"
#include "dius/platform_error.h"
#include "dius/platform_process.h"
#include "dius/platform_process_handle.h"
#include "dius/steady_clock.h"
#include "dius/sync_file.h"
#include "dius/system/process_result.h"

namespace dius::linux::epoll {
namespace ex = di::execution;

class Context;
struct ScheduleSender;
struct OperationBase;
struct WaitableOperationBase;
struct OpenSender;
struct AdoptFileSender;

struct OperationBase : di::IntrusiveForwardListNode<> {
    virtual void execute() = 0;
};

struct WaitableOperationBase : OperationBase {
    i32 fd { -1 };
    EventType events { EventType::None };

    explicit WaitableOperationBase(i32 fd, EventType events) : fd(fd), events(events) {}

    virtual void notify() = 0;
    virtual void terminate() = 0;
};

struct SignalOperationBase : OperationBase {
    Signal signal {};

    explicit SignalOperationBase(Signal signal) : signal(signal) {}

    virtual void notify() = 0;
    virtual void terminate() = 0;
};

struct TimeoutOperationBase : OperationBase {
    SteadyClock::TimePoint deadline {};

    explicit TimeoutOperationBase(SteadyClock::TimePoint deadline) : deadline(deadline) {}

    virtual void notify() = 0;
    virtual void terminate() = 0;
};

struct InotifyOperationBase : OperationBase {
    di::Path path;
    Inotify::EventType events { Inotify::EventType::None };
    i32 token { -1 };
    di::Error error { PosixError::Success };

    explicit InotifyOperationBase(di::Path path, Inotify::EventType events) : path(di::move(path)), events(events) {}

    virtual void notify() = 0;
    virtual void terminate() = 0;
};

class Scheduler {
public:
    Context* context { nullptr };

private:
    constexpr friend auto operator==(Scheduler const&, Scheduler const&) -> bool = default;

    friend auto tag_invoke(di::Tag<ex::schedule>, Scheduler self) -> ScheduleSender;
};

class Context {
public:
    static auto create() -> di::Result<Context>;

    explicit Context(Handle epoll_handle, Eventfd eventfd, Signalfd signalfd, Inotify inotify);

    Context(Context&& other)
        : m_epoll_handle(di::move(other.m_epoll_handle))
        , m_eventfd(di::move(other.m_eventfd))
        , m_signalfd(di::move(other.m_signalfd))
        , m_inotify(di::move(other.m_inotify)) {}

    auto get_scheduler() -> Scheduler { return Scheduler(this); }
    void run();
    void finish();

    auto try_start(OperationBase&) -> bool;
    void add_waiter(WaitableOperationBase&);
    void add_waiter(SignalOperationBase&);
    void add_waiter(TimeoutOperationBase&);
    void add_waiter(InotifyOperationBase&);
    void cancel(WaitableOperationBase&);
    void cancel(SignalOperationBase&);
    void cancel(TimeoutOperationBase&);
    void cancel(InotifyOperationBase&);
    void wake();

private:
    void update_inotify(i32 token, Inotify::EventType new_events,
                        di::TreeMap<i32, di::IntrusiveForwardList<InotifyOperationBase>>::Iterator outer_it);

    void dispatch_event(i32 fd, EventType events);
    void dispatch_signal();
    void process_timeouts();
    void dispatch_inotify(Inotify::Event const& event);

    Handle m_epoll_handle;
    Eventfd m_eventfd;
    Signalfd m_signalfd;
    Inotify m_inotify;
    di::Atomic<i32> m_staring_operations { 0 };
    di::Atomic<bool> m_need_wake { false };
    di::IntrusiveAtomicBatchQueue<OperationBase> m_queued_operations;
    di::TreeMap<i32, di::IntrusiveForwardList<WaitableOperationBase>> m_waiting_operations;
    di::TreeMap<Signal, di::IntrusiveForwardList<SignalOperationBase>> m_signal_operations;
    di::IntrusiveForwardList<TimeoutOperationBase> m_timeout_operations;
    di::TreeMap<i32, di::IntrusiveForwardList<InotifyOperationBase>> m_inotify_waiters;
    di::TreeMap<di::Path, i32> m_inotify_tokens;
    di::TreeMap<i32, di::Path> m_inotify_paths;
    di::TreeMap<i32, Inotify::EventType> m_inotify_state;
    bool m_signal_set_changed { false };
};

struct Env {
    Context* parent { nullptr };

    template<typename CPO>
    requires(!di::concepts::SameAs<CPO, di::Tag<ex::set_stopped>>)
    constexpr friend auto tag_invoke(ex::GetCompletionScheduler<CPO>, Env const& self) {
        return self.parent->get_scheduler();
    }
};

template<typename Self, typename Rec, bool cancellable = true>
struct OperationImplBase : OperationBase {
    Context* context { nullptr };
    [[no_unique_address]] Rec receiver;

    explicit OperationImplBase(Context* context, Rec receiver) : context(context), receiver(di::move(receiver)) {}

    void execute() override {
        if constexpr (cancellable) {
            if (ex::get_stop_token(ex::get_env(this->receiver)).stop_requested()) {
                ex::set_stopped(di::move(this->receiver));
            }
        }

        auto result = static_cast<Self&>(*this).do_execute();
        if constexpr (di::concepts::Expected<decltype(result)>) {
            if (result.has_value()) {
                if constexpr (di::concepts::ExpectedOf<decltype(result), void>) {
                    ex::set_value(di::move(this->receiver));
                } else {
                    ex::set_value(di::move(this->receiver), di::move(result).value());
                }
            } else {
                ex::set_error(di::move(this->receiver), di::move(result).error());
            }
        } else if constexpr (di::concepts::SameAs<di::Void, decltype(result)>) {
            ex::set_value(di::move(this->receiver));
        } else {
            ex::set_value(di::move(this->receiver), di::move(result));
        }
    }

    friend void tag_invoke(di::Tag<ex::start>, Self& self) {
        if (!self.context->try_start(self)) {
            // For non cancellable operations (close) we should still attempt the operation even though
            // we must report stopped(). We can succeed in this case because it would violate the contract
            // that our completion scheduler is the epoll context.
            if constexpr (!cancellable) {
                (void) self.do_execute();
            }
            ex::set_stopped(di::move(self.receiver));
        }
    }
};

template<typename Outer>
struct CancelOperation : OperationBase {
    explicit CancelOperation(Outer* outer) : outer(outer) {}

    Outer* outer { nullptr };

    void execute() override {
        // We can use relaxed memory order because we're running on the context and so therefore
        // cannot possibly race with normal completion. Add we cannot race with the stop callback
        // as the stop callback already fired. This additionally means we can tell at this point
        // whether or not we've completed normally (and thus do not need to cancel()).
        if (!outer->value.has_value()) {
            outer->context->cancel(*outer);
        }
        outer->complete();
    }
};

template<typename Outer>
struct WaitableOperationStopCallbackFunction {
    Outer* outer { nullptr };

    void operator()() const noexcept { outer->try_cancel(); }
};

template<typename Self, typename Rec, typename Base, typename T, bool has_notify_error = false>
struct WaitableOperationImplBase : Base {
    using StopCallback = WaitableOperationStopCallbackFunction<WaitableOperationImplBase>;
    using StopToken = di::meta::StopTokenOf<di::meta::EnvOf<Rec>>;
    using StopCallbackStorage = StopToken::template CallbackType<StopCallback>;

    Context* context { nullptr };
    [[no_unique_address]] Rec receiver;
    di::Optional<T> value;
    di::Atomic<bool> get_to_complete {};
    di::Optional<CancelOperation<WaitableOperationImplBase>> cancel_op;
    di::Optional<StopCallbackStorage> stop_callback;

    template<typename... Args>
    explicit WaitableOperationImplBase(Context* context, Rec&& receiver, Args&&... args)
        : Base(di::forward<Args>(args)...), context(context), receiver(di::move(receiver)) {}

    auto try_execute() -> di::Void { return {}; }

    void execute() override {
        auto stop_token = ex::get_stop_token(ex::get_env(this->receiver));
        if (stop_token.stop_requested()) {
            ex::set_stopped(di::move(this->receiver));
        } else {
            auto result = static_cast<Self&>(*this).try_execute();
            if constexpr (!di::SameAs<decltype(result), di::Void>) {
                if (result != di::Unexpected(PosixError::ResourceUnavailableTryAgain)) {
                    // Complete immediately.
                    this->value = di::move(result);
                    this->complete();
                    return;
                }
            }
            this->add_waiter(stop_token);
        }
    }

    void notify() override {
        // Try to let allow ourselves to complete (and thus win the race vs. starting the cancel op).
        auto expected = false;
        auto should_complete = this->get_to_complete.compare_exchange_strong(expected, true, di::MemoryOrder::Relaxed);

        this->value = static_cast<Self&>(*this).do_notify();
        if (should_complete) {
            this->complete();
        }
    }

    void terminate() override { ex::set_stopped(di::move(this->receiver)); }

    void add_waiter(StopToken stop_token) {
        this->context->add_waiter(*this);
        this->stop_callback.emplace(stop_token, StopCallback(this));
    }

    void try_cancel() {
        auto expected = false;
        auto should_cancel = this->get_to_complete.compare_exchange_strong(expected, true, di::MemoryOrder::Relaxed);
        if (should_cancel) {
            auto& op = cancel_op.emplace(this);
            this->context->try_start(op);
        }
    }

    void complete() {
        cancel_op.reset();
        stop_callback.reset();

        if (!value.has_value()) {
            return ex::set_stopped(di::move(this->receiver));
        }
        if constexpr (di::concepts::Expected<T>) {
            if (value.value().has_value()) {
                if constexpr (di::concepts::ExpectedOf<T, void>) {
                    ex::set_value(di::move(this->receiver));
                } else {
                    ex::set_value(di::move(this->receiver), di::move(value.value()).value());
                }
            } else {
                ex::set_error(di::move(this->receiver), di::move(value.value()).error());
            }
        } else if constexpr (di::concepts::SameAs<di::Void, T>) {
            ex::set_value(di::move(this->receiver));
        } else {
            ex::set_value(di::move(this->receiver), di::move(value.value()));
        }
    }

    friend void tag_invoke(di::Tag<ex::start>, Self& self) {
        if (!self.context->try_start(self)) {
            ex::set_stopped(di::move(self.receiver));
        }
    }
};

template<typename Self, typename Value = di::Void, bool fallible = true>
struct SenderBase {
    using is_sender = void;

    using ValueCompletion = di::meta::Conditional<di::SameAs<di::Void, Value>, di::SetValue(), di::SetValue(Value)>;
    using CompletionSignatures =
        di::meta::Conditional<fallible,
                              di::CompletionSignatures<ValueCompletion, di::SetError(di::Error), di::SetStopped()>,
                              di::CompletionSignatures<ValueCompletion, di::SetStopped()>>;

    Context* context { nullptr };

    constexpr friend auto tag_invoke(di::Tag<ex::get_env>, Self const& self) { return Env(self.context); }
};

struct ScheduleSender : SenderBase<ScheduleSender, di::Void, false> {
    using Base = SenderBase<ScheduleSender, di::Void, false>;

    explicit ScheduleSender(Context* context) : Base(context) {}

    template<typename Rec>
    struct Op : OperationImplBase<Op<Rec>, Rec> {
        using Base = OperationImplBase<Op, Rec>;

        Op(Context* context, Rec&& receiver) : Base(context, di::move(receiver)) {}

        auto do_execute() -> di::Void { return {}; }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, ScheduleSender self, Rec receiver) {
        return Op<Rec> { self.context, di::move(receiver) };
    }
};

struct CloseSender : SenderBase<CloseSender> {
    using Base = SenderBase<CloseSender>;

    explicit CloseSender(Context* context, i32 fd) : Base(context), fd(fd) {}

    i32 fd { -1 };

    template<typename Rec>
    struct Op : OperationImplBase<Op<Rec>, Rec, false> {
        using Base = OperationImplBase<Op, Rec, false>;

        i32 fd { -1 };

        Op(Context* context, i32 fd, Rec&& receiver) : Base(context, di::move(receiver)), fd(fd) {}

        auto do_execute() -> di::Result<> { return SyncFile(SyncFile::Owned::Yes, fd).close(); }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, CloseSender self, Rec receiver) {
        return Op<Rec> { self.context, self.fd, di::move(receiver) };
    }
};

struct ReadSomeSender : SenderBase<ReadSomeSender, usize> {
    using Base = SenderBase<ReadSomeSender, usize>;

    explicit ReadSomeSender(Context* context, i32 fd, ReadSomeArgs args)
        : Base(context), fd(fd), args(di::move(args)) {}

    i32 fd { -1 };
    ReadSomeArgs args;

    template<typename Rec>
    struct Op : WaitableOperationImplBase<Op<Rec>, Rec, WaitableOperationBase, di::Result<usize>> {
        using Base = WaitableOperationImplBase<Op, Rec, WaitableOperationBase, di::Result<usize>>;

        ReadSomeArgs args;

        Op(Context* context, i32 fd, ReadSomeArgs args, Rec&& receiver)
            : Base(context, di::move(receiver), fd, EventType::Read), args(di::move(args)) {}

        auto try_execute() { return do_notify(); }

        auto do_notify() -> di::Result<usize> {
            auto file = SyncFile(SyncFile::Owned::No, this->fd);
            if (args.offset) {
                return file.read_some(args.offset.value(), args.buffer);
            }
            return file.read_some(args.buffer);
        }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, ReadSomeSender self, Rec receiver) {
        return Op<Rec> { self.context, self.fd, di::move(self.args), di::move(receiver) };
    }
};

struct WriteSomeSender : SenderBase<WriteSomeSender, usize> {
    using Base = SenderBase<WriteSomeSender, usize>;

    explicit WriteSomeSender(Context* context, i32 fd, WriteSomeArgs args)
        : Base(context), fd(fd), args(di::move(args)) {}

    i32 fd { -1 };
    WriteSomeArgs args;

    template<typename Rec>
    struct Op : WaitableOperationImplBase<Op<Rec>, Rec, WaitableOperationBase, di::Result<usize>> {
        using Base = WaitableOperationImplBase<Op, Rec, WaitableOperationBase, di::Result<usize>>;

        WriteSomeArgs args;

        Op(Context* context, i32 fd, WriteSomeArgs args, Rec&& receiver)
            : Base(context, di::move(receiver), fd, EventType::Write), args(di::move(args)) {}

        auto try_execute() { return do_notify(); }

        auto do_notify() -> di::Result<usize> {
            auto file = SyncFile(SyncFile::Owned::No, this->fd);
            if (args.offset) {
                return file.write_some(args.offset.value(), args.buffer);
            }
            return file.write_some(args.buffer);
        }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, WriteSomeSender self, Rec receiver) {
        return Op<Rec> { self.context, self.fd, di::move(self.args), di::move(receiver) };
    }
};

struct PidfdWaitSender : SenderBase<PidfdWaitSender, system::ProcessResult> {
    using Base = SenderBase<PidfdWaitSender, system::ProcessResult>;

    explicit PidfdWaitSender(Context* context, system::ProcessHandle process)
        : Base(context), process(di::move(process)) {}

    system::ProcessHandle process;

    template<typename Rec>
    struct Op : WaitableOperationImplBase<Op<Rec>, Rec, WaitableOperationBase, di::Result<system::ProcessResult>> {
        using Base = WaitableOperationImplBase<Op, Rec, WaitableOperationBase, di::Result<system::ProcessResult>>;

        system::ProcessHandle process;

        Op(Context* context, system::ProcessHandle process, Rec&& receiver)
            : Base(context, di::move(receiver), process.pidfd(), EventType::Read), process(di::move(process)) {}

        auto do_notify() -> di::Result<system::ProcessResult> { return process.sync_wait(); }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, PidfdWaitSender self, Rec receiver) {
        return Op<Rec> { self.context, di::move(self.process), di::move(receiver) };
    }
};

struct FileToken {
    Context* context { nullptr };
    i32 fd { -1 };

    auto close() -> CloseSender { return CloseSender(context, fd); }

    friend auto tag_invoke(di::Tag<read_some>, FileToken const& self, di::Span<byte> buffer, di::Optional<u64> offset) {
        return ReadSomeSender(self.context, self.fd, ReadSomeArgs(buffer, offset));
    }

    friend auto tag_invoke(di::Tag<write_some>, FileToken const& self, di::Span<byte const> buffer,
                           di::Optional<u64> offset) {
        return WriteSomeSender(self.context, self.fd, WriteSomeArgs(buffer, offset));
    }
};

struct ConnectUnixSender : SenderBase<ConnectUnixSender> {
    using Base = SenderBase<ConnectUnixSender>;

    explicit ConnectUnixSender(Context* context, i32 fd, ConnectUnixArgs args)
        : Base(context), fd(fd), args(di::move(args)) {}

    i32 fd { -1 };
    ConnectUnixArgs args;

    template<typename Rec>
    struct Op : WaitableOperationImplBase<Op<Rec>, Rec, WaitableOperationBase, di::Result<>> {
        using Base = WaitableOperationImplBase<Op, Rec, WaitableOperationBase, di::Result<>>;

        ConnectUnixArgs args;

        Op(Context* context, i32 fd, ConnectUnixArgs args, Rec&& receiver)
            : Base(context, di::move(receiver), fd, EventType::Write), args(di::move(args)) {}

        void execute() override {
            auto stop_token = ex::get_stop_token(ex::get_env(this->receiver));
            if (stop_token.stop_requested()) {
                ex::set_stopped(di::move(this->receiver));
            } else {
                auto result = net::SyncSocket(net::SyncSocket::Owned::No, this->fd).connect(args.address);
                if (result.has_value()) {
                    ex::set_value(di::move(this->receiver));
                } else if (result.error() != PosixError::OperationInProgress) {
                    ex::set_error(di::move(this->receiver), di::move(result).error());
                } else {
                    this->add_waiter(stop_token);
                }
            }
        }

        auto do_notify() -> di::Result<> { return net::SyncSocket(net::SyncSocket::Owned::No, this->fd).get_error(); }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, ConnectUnixSender self, Rec receiver) {
        return Op<Rec> { self.context, self.fd, di::move(self.args), di::move(receiver) };
    }
};

struct BindUnixSender : SenderBase<BindUnixSender, FileToken> {
    using Base = SenderBase<BindUnixSender, FileToken>;

    explicit BindUnixSender(Context* context, i32 fd, BindUnixArgs args)
        : Base(context), fd(fd), args(di::move(args)) {}

    i32 fd { -1 };
    BindUnixArgs args;

    template<typename Rec>
    struct Op : OperationImplBase<Op<Rec>, Rec> {
        using Base = OperationImplBase<Op, Rec>;

        i32 fd { -1 };
        BindUnixArgs args;

        Op(Context* context, i32 fd, BindUnixArgs args, Rec&& receiver)
            : Base(context, di::move(receiver)), fd(fd), args(di::move(args)) {}

        auto do_execute() -> di::Result<> { return net::SyncSocket(net::SyncSocket::Owned::No, fd).bind(args.address); }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, BindUnixSender self, Rec receiver) {
        return Op<Rec> { self.context, self.fd, di::move(self.args), di::move(receiver) };
    }
};

struct ShutdownSender : SenderBase<ShutdownSender, FileToken> {
    using Base = SenderBase<ShutdownSender, FileToken>;

    explicit ShutdownSender(Context* context, i32 fd, ShutdownArgs args)
        : Base(context), fd(fd), args(di::move(args)) {}

    i32 fd { -1 };
    ShutdownArgs args;

    template<typename Rec>
    struct Op : OperationImplBase<Op<Rec>, Rec> {
        using Base = OperationImplBase<Op, Rec>;

        i32 fd { -1 };
        ShutdownArgs args;

        Op(Context* context, i32 fd, ShutdownArgs args, Rec&& receiver)
            : Base(context, di::move(receiver)), fd(fd), args(di::move(args)) {}

        auto do_execute() -> di::Result<> {
            return net::SyncSocket(net::SyncSocket::Owned::No, fd).shutdown(args.mode);
        }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, ShutdownSender self, Rec receiver) {
        return Op<Rec> { self.context, self.fd, di::move(self.args), di::move(receiver) };
    }
};

struct ListenSender : SenderBase<ListenSender, FileToken> {
    using Base = SenderBase<ListenSender, FileToken>;

    explicit ListenSender(Context* context, i32 fd, ListenArgs args) : Base(context), fd(fd), args(di::move(args)) {}

    i32 fd { -1 };
    ListenArgs args;

    template<typename Rec>
    struct Op : OperationImplBase<Op<Rec>, Rec> {
        using Base = OperationImplBase<Op, Rec>;

        i32 fd { -1 };
        ListenArgs args;

        Op(Context* context, i32 fd, ListenArgs args, Rec&& receiver)
            : Base(context, di::move(receiver)), fd(fd), args(di::move(args)) {}

        auto do_execute() -> di::Result<> {
            return net::SyncSocket(net::SyncSocket::Owned::No, fd).listen(args.backlog);
        }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, ListenSender self, Rec receiver) {
        return Op<Rec> { self.context, self.fd, di::move(self.args), di::move(receiver) };
    }
};

struct SocketToken {
    Context* context { nullptr };
    i32 fd { -1 };

    auto close() -> CloseSender { return CloseSender(context, fd); }

    friend auto tag_invoke(di::Tag<read_some>, SocketToken const& self, di::Span<byte> buffer, di::Optional<u64>) {
        return ReadSomeSender(self.context, self.fd, ReadSomeArgs(buffer, {}));
    }

    friend auto tag_invoke(di::Tag<write_some>, SocketToken const& self, di::Span<byte const> buffer,
                           di::Optional<u64>) {
        return WriteSomeSender(self.context, self.fd, WriteSomeArgs(buffer, {}));
    }

    friend auto tag_invoke(di::Tag<listen>, SocketToken const& self, i32 backlog) {
        return ListenSender(self.context, self.fd, ListenArgs(backlog));
    }

    friend auto tag_invoke(di::Tag<shutdown>, SocketToken const& self, net::Shutdown mode) {
        return ShutdownSender(self.context, self.fd, ShutdownArgs(mode));
    }

    friend auto tag_invoke(di::Tag<bind>, SocketToken const& self, net::UnixAddress address) {
        return BindUnixSender(self.context, self.fd, BindUnixArgs(di::move(address)));
    }

    friend auto tag_invoke(di::Tag<connect>, SocketToken const& self, net::UnixAddress address) {
        return ConnectUnixSender(self.context, self.fd, ConnectUnixArgs(di::move(address)));
    }
};

struct AcceptSender : SenderBase<AcceptSender, SocketToken> {
    using Base = SenderBase<AcceptSender, SocketToken>;

    explicit AcceptSender(Context* context, i32 fd, AcceptArgs args) : Base(context), fd(fd), args(di::move(args)) {}

    i32 fd { -1 };
    AcceptArgs args;

    template<typename Rec>
    struct Op : WaitableOperationImplBase<Op<Rec>, Rec, WaitableOperationBase, di::Result<SocketToken>> {
        using Base = WaitableOperationImplBase<Op, Rec, WaitableOperationBase, di::Result<SocketToken>>;

        AcceptArgs args;

        Op(Context* context, i32 fd, AcceptArgs args, Rec&& receiver)
            : Base(context, di::move(receiver), fd, EventType::Read), args(di::move(args)) {}

        auto do_notify() -> di::Result<SocketToken> {
            return net::SyncSocket(net::SyncSocket::Owned::No, this->fd)
                .accept(args.open_flags | OpenFlags::NonBlocking)
                .transform([&](net::SyncSocket socket) {
                    return SocketToken(this->context, socket.leak_file_descriptor());
                });
        }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, AcceptSender self, Rec receiver) {
        return Op<Rec> { self.context, self.fd, di::move(self.args), di::move(receiver) };
    }
};

struct SignalledSender : SenderBase<SignalledSender> {
    using Base = SenderBase<SignalledSender>;

    explicit SignalledSender(Context* context, Signal signal) : Base(context), signal(signal) {}

    Signal signal {};

    template<typename Rec>
    struct Op : WaitableOperationImplBase<Op<Rec>, Rec, SignalOperationBase, di::Void> {
        using Base = WaitableOperationImplBase<Op<Rec>, Rec, SignalOperationBase, di::Void>;

        Op(Context* context, Signal signal, Rec&& receiver) : Base(context, di::move(receiver), signal) {}

        auto do_notify() -> di::Void { return {}; }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, SignalledSender self, Rec receiver) {
        return Op<Rec> { self.context, self.signal, di::move(receiver) };
    }
};

struct TimeoutSender : SenderBase<TimeoutSender> {
    using Base = SenderBase<TimeoutSender>;

    explicit TimeoutSender(Context* context, SteadyClock::TimePoint deadline) : Base(context), deadline(deadline) {}

    SteadyClock::TimePoint deadline {};

    template<typename Rec>
    struct Op : WaitableOperationImplBase<Op<Rec>, Rec, TimeoutOperationBase, di::Void> {
        using Base = WaitableOperationImplBase<Op<Rec>, Rec, TimeoutOperationBase, di::Void>;

        Op(Context* context, SteadyClock::TimePoint deadline, Rec&& receiver)
            : Base(context, di::move(receiver), deadline) {}

        auto do_notify() -> di::Void { return {}; }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, TimeoutSender self, Rec receiver) {
        return Op<Rec> { self.context, self.deadline, di::move(receiver) };
    }
};

struct ModifiedSender : SenderBase<ModifiedSender> {
    using Base = SenderBase<ModifiedSender>;

    explicit ModifiedSender(Context* context, di::Path path) : Base(context), path(di::move(path)) {}

    di::Path path;

    template<typename Rec>
    struct Op : WaitableOperationImplBase<Op<Rec>, Rec, InotifyOperationBase, di::Result<>, true> {
        using Base = WaitableOperationImplBase<Op<Rec>, Rec, InotifyOperationBase, di::Result<>, true>;

        Op(Context* context, di::Path path, Rec&& receiver)
            : Base(context, di::move(receiver), di::move(path), Inotify::EventType::WriteClosed) {}

        auto do_notify() -> di::Result<> {
            if (this->error.success()) {
                return {};
            }
            return di::Unexpected(di::move(this->error));
        }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, ModifiedSender self, Rec receiver) {
        return Op<Rec> { self.context, di::move(self.path), di::move(receiver) };
    }
};

struct OpenSender : SenderBase<OpenSender, FileToken> {
    using Base = SenderBase<OpenSender, FileToken>;

    explicit OpenSender(Context* context, OpenArgs args) : Base(context), args(di::move(args)) {}

    OpenArgs args;

    template<typename Rec>
    struct Op : OperationImplBase<Op<Rec>, Rec> {
        using Base = OperationImplBase<Op, Rec>;

        OpenArgs args;

        Op(Context* context, OpenArgs args, Rec&& receiver) : Base(context, di::move(receiver)), args(di::move(args)) {}

        auto do_execute() -> di::Result<FileToken> {
            auto file = TRY(open_sync(args.path.view(), args.open_mode, args.create_mode,
                                      args.open_flags | OpenFlags::NonBlocking));

            // The file descriptor is managed via the async resource.
            return FileToken(this->context, file.leak_file_descriptor());
        }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, OpenSender self, Rec receiver) {
        return Op<Rec> { self.context, di::move(self.args), di::move(receiver) };
    }
};

struct AdoptFileSender : SenderBase<AdoptFileSender, FileToken> {
    using Base = SenderBase<AdoptFileSender, FileToken>;

    explicit AdoptFileSender(Context* context, SyncFile file) : Base(context), file(di::move(file)) {}

    SyncFile file;

    template<typename Rec>
    struct Op : OperationImplBase<Op<Rec>, Rec> {
        using Base = OperationImplBase<Op, Rec>;

        SyncFile file;

        Op(Context* context, SyncFile file, Rec&& receiver) : Base(context, di::move(receiver)), file(di::move(file)) {}

        auto do_execute() -> di::Result<FileToken> {
            TRY(file.set_open_flags(OpenFlags::NonBlocking));
            return FileToken(this->context, file.leak_file_descriptor());
        }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, AdoptFileSender self, Rec receiver) {
        return Op<Rec> { self.context, di::move(self.file), di::move(receiver) };
    }
};

struct MakeUnixSocketSender : SenderBase<MakeUnixSocketSender, SocketToken> {
    using Base = SenderBase<MakeUnixSocketSender, SocketToken>;

    explicit MakeUnixSocketSender(Context* context, MakeUnixSocketArgs args) : Base(context), args(di::move(args)) {}

    MakeUnixSocketArgs args;

    template<typename Rec>
    struct Op : OperationImplBase<Op<Rec>, Rec> {
        using Base = OperationImplBase<Op, Rec>;

        Op(Context* context, MakeUnixSocketArgs args, Rec&& receiver)
            : Base(context, di::move(receiver)), args(di::move(args)) {}

        MakeUnixSocketArgs args;

        auto do_execute() -> di::Result<SocketToken> {
            auto file = TRY(net::make_unix_socket_sync(args.open_flags | OpenFlags::NonBlocking));

            // The file descriptor is managed via the async resource.
            return SocketToken(this->context, file.leak_file_descriptor());
        }
    };

    template<di::ReceiverOf<Base::CompletionSignatures> Rec>
    friend auto tag_invoke(di::Tag<ex::connect>, MakeUnixSocketSender self, Rec receiver) {
        return Op<Rec> { self.context, di::move(self.args), di::move(receiver) };
    }
};

struct File : ex::ResourceHelper<File, FileToken, OpenSender, CloseSender> {
    explicit File(Context* context, OpenArgs args) : context(context), args(di::move(args)) {}

    auto open() { return OpenSender(context, di::move(args)); }
    auto get_env() const -> Env { return Env(context); }

    Context* context { nullptr };
    OpenArgs args;
};

struct AdoptedFile : ex::ResourceHelper<AdoptedFile, FileToken, AdoptFileSender, CloseSender> {
    explicit AdoptedFile(Context* context, SyncFile file) : context(context), file(di::move(file)) {}

    auto open() { return AdoptFileSender(context, di::move(file)); }
    auto get_env() const -> Env { return Env(context); }

    Context* context { nullptr };
    SyncFile file {};
};

struct UnixSocket : ex::ResourceHelper<UnixSocket, SocketToken, MakeUnixSocketSender, CloseSender> {
    explicit UnixSocket(Context* context, MakeUnixSocketArgs args) : context(context), args(di::move(args)) {}

    auto open() { return MakeUnixSocketSender(context, di::move(args)); }
    auto get_env() const -> Env { return Env(context); }

    Context* context { nullptr };
    MakeUnixSocketArgs args;
};

struct AcceptedSocket : ex::ResourceHelper<AcceptedSocket, SocketToken, AcceptSender, CloseSender> {
    explicit AcceptedSocket(Context* context, i32 fd, AcceptArgs args)
        : context(context), fd(fd), args(di::move(args)) {}

    auto open() { return AcceptSender(context, fd, di::move(args)); }
    auto get_env() const -> Env { return Env(context); }

    Context* context { nullptr };
    i32 fd { -1 };
    AcceptArgs args;
};

inline auto tag_invoke(di::Tag<ex::schedule>, Scheduler self) -> ScheduleSender {
    return ScheduleSender { self.context };
}

inline auto tag_invoke(di::Tag<open>, Scheduler self, di::Path path, OpenMode open_mode, OpenFlags open_flags,
                       u16 create_mode) {
    return di::make_deferred<File>(self.context, OpenArgs(di::move(path), open_mode, open_flags, create_mode));
}

inline auto tag_invoke(di::Tag<adopt_file>, Scheduler self, SyncFile file) {
    return di::make_deferred<AdoptedFile>(self.context, di::move(file));
}

inline auto tag_invoke(di::Tag<make_unix_socket>, Scheduler self, OpenFlags open_flags) {
    return di::make_deferred<UnixSocket>(self.context, MakeUnixSocketArgs(open_flags));
}

inline auto tag_invoke(di::Tag<accept>, SocketToken const& token, OpenFlags open_flags) {
    return di::make_deferred<AcceptedSocket>(token.context, token.fd, AcceptArgs(open_flags));
}

inline auto tag_invoke(di::Tag<signalled>, Scheduler self, Signal signal) {
    return SignalledSender(self.context, signal);
}

inline auto tag_invoke(di::Tag<ex::now>, Scheduler) -> SteadyClock::TimePoint {
    return SteadyClock::now();
}

inline auto tag_invoke(di::Tag<ex::schedule_at>, Scheduler self, SteadyClock::TimePoint deadline) {
    return TimeoutSender(self.context, deadline);
}

inline auto sigchild_waiter(Scheduler self, system::ProcessHandle process) -> di::Lazy<system::ProcessResult> {
    for (;;) {
        auto result = process.sync_wait(true);
        if (result == di::Unexpected(PosixError::ResourceUnavailableTryAgain)) {
            co_await SignalledSender(self.context, Signal::Child);
            continue;
        }
        co_return CO_TRY(di::move(result));
    }
}

using SigchildWaitSender = decltype(sigchild_waiter(di::declval<Scheduler>(), di::declval<system::ProcessHandle>()));

inline auto tag_invoke(di::Tag<wait>, Scheduler self, system::ProcessHandle process)
    -> di::execution::VariantSender<SigchildWaitSender, PidfdWaitSender> {
    if (process.pidfd() == -1) {
        return sigchild_waiter(self, di::move(process));
    }
    return PidfdWaitSender(self.context, di::move(process));
}

inline auto tag_invoke(di::Tag<modified>, Scheduler self, di::Path path) {
    return ModifiedSender(self.context, di::move(path));
}
}

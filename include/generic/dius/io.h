#pragma once

#include "di/execution/interface/run.h"
#include "di/execution/io/read_exactly.h"
#include "di/execution/io/read_some.h"
#include "di/execution/io/write_exactly.h"
#include "di/execution/io/write_some.h"
#include "dius/net/address.h"
#include "dius/net/socket.h"
#include "dius/sync_file.h"

namespace dius {
using di::execution::read_exactly;
using di::execution::read_some;
using di::execution::write_exactly;
using di::execution::write_some;

struct OpenArgs {
    di::Path path;
    OpenMode open_mode { OpenMode::Readonly };
    OpenFlags open_flags { OpenFlags::None };
    u16 create_mode { 0 };
};

struct ReadSomeArgs {
    di::Span<byte> buffer;
    di::Optional<u64> offset;
};

struct WriteSomeArgs {
    di::Span<byte const> buffer;
    di::Optional<u64> offset;
};

struct MakeUnixSocketArgs {
    OpenFlags open_flags { OpenFlags::None };
};

struct AcceptArgs {
    OpenFlags open_flags { OpenFlags::None };
};

struct ConnectUnixArgs {
    net::UnixAddress address;
};

struct BindUnixArgs {
    net::UnixAddress address;
};

struct ShutdownArgs {
    net::Shutdown mode { net::Shutdown::ReadWrite };
};

struct ListenArgs {
    i32 backlog { 0 };
};

namespace open_ns {
    struct Function {
        template<di::concepts::Scheduler Sched>
        requires(di::concepts::TagInvocable<Function, Sched, di::Path, OpenMode, OpenFlags, u16>)
        static auto operator()(Sched&& sched, di::Path path, OpenMode open_mode, OpenFlags open_flags = OpenFlags::None,
                               u16 create_mode = 0666) {
            static_assert(di::concepts::AsyncResource<di::meta::InvokeResult<
                              di::meta::TagInvokeResult<Function, Sched, di::Path, OpenMode, OpenFlags, u16>>>,
                          "dius::open() customizations must return a deferred di::AsyncResource instance.");
            return tag_invoke(Function {}, di::forward<Sched>(sched), di::move(path), open_mode, open_flags,
                              create_mode);
        }
    };
}

constexpr inline auto open = open_ns::Function {};

namespace adopt_file_ns {
    struct Function {
        template<di::concepts::Scheduler Sched>
        requires(di::concepts::TagInvocable<Function, Sched, SyncFile>)
        static auto operator()(Sched&& sched, dius::SyncFile file) {
            static_assert(di::concepts::AsyncResource<
                              di::meta::InvokeResult<di::meta::TagInvokeResult<Function, Sched, SyncFile>>>,
                          "dius::adopt_file() customizations must return a deferred di::AsyncResource instance.");
            return tag_invoke(Function {}, di::forward<Sched>(sched), di::move(file));
        }
    };
}

constexpr inline auto adopt_file = adopt_file_ns::Function {};

namespace make_unix_socket_ns {
    struct Function {
        template<di::concepts::Scheduler Sched>
        requires(di::concepts::TagInvocable<Function, Sched, OpenFlags>)
        static auto operator()(Sched&& sched, OpenFlags open_flags = OpenFlags::None) {
            static_assert(di::concepts::AsyncResource<
                              di::meta::InvokeResult<di::meta::TagInvokeResult<Function, Sched, OpenFlags>>>,
                          "dius::make_unix_socket() customizations must return a deferred di::AsyncResource instance.");
            return tag_invoke(Function {}, di::forward<Sched>(sched), open_flags);
        }
    };
}

constexpr inline auto make_unix_socket = make_unix_socket_ns::Function {};

namespace accept_ns {
    struct Function {
        template<typename Token>
        requires(di::concepts::TagInvocable<Function, Token, OpenFlags>)
        static auto operator()(Token token, OpenFlags open_flags = OpenFlags::None) {
            static_assert(di::concepts::AsyncResource<
                              di::meta::InvokeResult<di::meta::TagInvokeResult<Function, Token, OpenFlags>>>,
                          "dius::accept() customizations must return a deferred di::AsyncResource instance.");
            return tag_invoke(Function {}, di::forward<Token>(token), open_flags);
        }
    };
}

constexpr inline auto accept = accept_ns::Function {};

namespace bind_ns {
    struct Function {
        template<typename Token>
        requires(di::concepts::TagInvocable<Function, Token, net::UnixAddress>)
        static auto operator()(Token token, net::UnixAddress address) -> auto {
            static_assert(di::concepts::Sender<di::meta::TagInvokeResult<Function, Token, net::UnixAddress>>,
                          "dius::bind() customiziations must return a sender");
            return tag_invoke(Function {}, token, di::move(address));
        }
    };
}

constexpr inline auto bind = bind_ns::Function {};

namespace connect_ns {
    struct Function {
        template<typename Token>
        requires(di::concepts::TagInvocable<Function, Token, net::UnixAddress>)
        static auto operator()(Token token, net::UnixAddress address) -> auto {
            static_assert(di::concepts::Sender<di::meta::TagInvokeResult<Function, Token, net::UnixAddress>>,
                          "dius::connect() customiziations must return a sender");
            return tag_invoke(Function {}, token, di::move(address));
        }
    };
}

constexpr inline auto connect = connect_ns::Function {};

namespace listen_ns {
    struct Function {
        template<typename Token>
        requires(di::concepts::TagInvocable<Function, Token, i32>)
        static auto operator()(Token token, i32 backlog = 5) -> auto {
            static_assert(di::concepts::Sender<di::meta::TagInvokeResult<Function, Token, i32>>,
                          "dius::listen() customiziations must return a sender");
            return tag_invoke(Function {}, token, backlog);
        }
    };
}

constexpr inline auto listen = listen_ns::Function {};

namespace shutdown_ns {
    struct Function {
        template<typename Token>
        requires(di::concepts::TagInvocable<Function, Token, net::Shutdown>)
        static auto operator()(Token token, net::Shutdown shutdown) -> auto {
            static_assert(di::concepts::Sender<di::meta::TagInvokeResult<Function, Token, net::Shutdown>>,
                          "dius::shutdown() customiziations must return a sender");
            return tag_invoke(Function {}, token, shutdown);
        }
    };
}

constexpr inline auto shutdown = shutdown_ns::Function {};
}

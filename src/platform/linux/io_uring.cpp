#include "dius/linux/io_uring.h"

#include "di/container/algorithm/prelude.h"
#include "dius/system/system_call.h"

namespace dius::linux::io_uring {
auto sys_enter(unsigned int fd, unsigned int to_submit, unsigned int min_complete, unsigned int flags, void const* arg,
               size_t arg_size) -> di::Result<int> {
    return system::system_call<int>(system::Number::io_uring_enter, fd, to_submit, min_complete, flags, arg, arg_size);
}

auto sys_register(unsigned int fd, unsigned int op_code, void* arg, unsigned int nr_args) -> di::Result<int> {
    return system::system_call<int>(system::Number::io_uring_register, fd, op_code, arg, nr_args);
}

auto sys_setup(u32 entries, SetupParams* params) -> di::Result<SyncFile> {
    int fd = TRY(system::system_call<int>(system::Number(__NR_io_uring_setup), entries, params));
    return SyncFile(SyncFile::Owned::Yes, fd);
}

auto IoUringHandle::get_next_sqe() -> di::Optional<SQE&> {
    if (sq_pending >= sq_entry_count) {
        return di::nullopt;
    }

    auto head = sq_head->load(di::MemoryOrder::Relaxed);
    auto tail = head + sq_pending;

    auto& sqe = sq_array[tail & sq_mask];
    sq_index_array[tail & sq_mask] = tail & sq_mask;
    sq_pending++;
    return sqe;
}

auto IoUringHandle::get_next_cqe() -> di::Optional<CQE&> {
    auto tail = cq_tail->load(di::MemoryOrder::Acquire);
    auto head = cq_head->load(di::MemoryOrder::Relaxed);

    if (head == tail) {
        return di::nullopt;
    }

    auto& cqe = cq_array[head & cq_mask];
    cq_head->store(head + 1, di::MemoryOrder::Release);
    return cqe;
}

auto IoUringHandle::submit_and_wait() -> di::Result<void> {
    auto to_submit = sq_pending;
    if (sq_pending > 0) {
        sq_pending = 0;

        auto old_tail = sq_tail->load(di::MemoryOrder::Relaxed);
        sq_tail->store(old_tail + to_submit, di::MemoryOrder::Relaxed);
    }

    TRY(sys_enter(fd.file_descriptor(), to_submit, 1, 0, nullptr, 0));
    return {};
}

auto IoUringHandle::create() -> di::Result<IoUringHandle> {
    SetupParams params;
    di::fill_n(reinterpret_cast<di::Byte*>(&params), sizeof(params), 0_b);

    auto result = IoUringHandle {};

    result.fd = TRY(sys_setup(256, di::addressof(params)));

    auto cq_size = params.cq_off.cqes + params.cq_entries * sizeof(CQE);
    result.cq_region = TRY(result.fd.map(IORING_OFF_CQ_RING, cq_size, Protection::Readable | Protection::Writeable,
                                         MapFlags::Shared | MapFlags::Populate));

    auto cq_memory = result.cq_region.span();

    result.cq_entry_count = params.cq_entries;
    result.cq_mask = *cq_memory.typed_pointer_unchecked<unsigned int>(params.cq_off.ring_mask);
    result.cq_head = cq_memory.typed_pointer_unchecked<di::Atomic<unsigned int>>(params.cq_off.head);
    result.cq_tail = cq_memory.typed_pointer_unchecked<di::Atomic<unsigned int> const>(params.cq_off.tail);
    result.cq_overflow = cq_memory.typed_pointer_unchecked<di::Atomic<unsigned int> const>(params.cq_off.overflow);
    result.cq_array = cq_memory.typed_pointer_unchecked<CQE>(params.cq_off.cqes);

    auto sq_size = params.sq_off.array + params.sq_entries * sizeof(u32);
    result.sq_region = TRY(result.fd.map(IORING_OFF_SQ_RING, sq_size, Protection::Readable | Protection::Writeable,
                                         MapFlags::Shared | MapFlags::Populate));

    auto sq_memory = result.sq_region.span();

    result.sq_entry_count = params.sq_entries;
    result.sq_mask = *sq_memory.typed_pointer_unchecked<unsigned int>(params.sq_off.ring_mask);
    result.sq_head = sq_memory.typed_pointer_unchecked<di::Atomic<unsigned int> const>(params.sq_off.head);
    result.sq_tail = sq_memory.typed_pointer_unchecked<di::Atomic<unsigned int>>(params.sq_off.tail);
    result.sq_flags = sq_memory.typed_pointer_unchecked<di::Atomic<unsigned int> const>(params.sq_off.flags);
    result.sq_index_array = sq_memory.typed_pointer_unchecked<u32>(params.sq_off.array);

    auto sqe_size = params.sq_entries * sizeof(SQE);
    result.sqe_region = TRY(result.fd.map(IORING_OFF_SQES, sqe_size, Protection::Readable | Protection::Writeable,
                                          MapFlags::Shared | MapFlags::Populate));

    result.sq_array = result.sqe_region.span().typed_pointer_unchecked<SQE>(0);

    return result;
}
}

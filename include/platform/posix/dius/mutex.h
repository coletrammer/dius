#pragma once

#include <pthread.h>

namespace dius {
class Mutex {
public:
    Mutex();
    Mutex(Mutex const&) = delete;

    ~Mutex();

    void operator=(Mutex const&) = delete;

    void lock();

    auto try_lock() -> bool;

    void unlock();

    auto native_handle() -> pthread_mutex_t* { return &m_mutex; }

private:
    pthread_mutex_t m_mutex;
};
}

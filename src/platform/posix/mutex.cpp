#include "dius/mutex.h"

#include "di/assert/prelude.h"

namespace dius {
Mutex::Mutex() {
    pthread_mutex_init(&m_mutex, nullptr);
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&m_mutex);
}

void Mutex::lock() {
    auto rv = pthread_mutex_lock(&m_mutex);
    ASSERT_EQ(rv, 0);
}

auto Mutex::try_lock() -> bool {
    auto rv = pthread_mutex_trylock(&m_mutex);
    return rv == 0;
}

void Mutex::unlock() {
    auto rv = pthread_mutex_unlock(&m_mutex);
    ASSERT_EQ(rv, 0);
}
}

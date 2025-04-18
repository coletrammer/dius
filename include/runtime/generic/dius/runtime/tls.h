#pragma once

#include "di/vocab/span/prelude.h"

namespace dius::runtime {
struct TlsInfo {
    di::Span<byte const> tls_data;
    usize tls_size;
    usize tls_align;
};

auto get_tls_info() -> TlsInfo;
}

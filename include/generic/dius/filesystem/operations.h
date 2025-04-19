#pragma once

#include "di/container/path/prelude.h"

namespace dius::filesystem {
namespace detail {
    struct CreateRegularFileFunction {
        static auto operator()(di::PathView path) -> di::Result<bool>;
    };

    struct CreateDirectoryFunction {
        static auto operator()(di::PathView path) -> di::Result<bool>;
        static auto operator()(di::PathView path, di::PathView existing_path) -> di::Result<bool>;
    };

    struct CreateDirectoriesFunction {
        static auto operator()(di::PathView path) -> di::Result<bool>;
    };

    struct RemoveFunction {
        static auto operator()(di::PathView path) -> di::Result<bool>;
    };

    struct RemoveAllFunction {
        static auto operator()(di::PathView path) -> di::Result<umax>;
    };
}

constexpr inline auto create_regular_file = detail::CreateRegularFileFunction {};
constexpr inline auto create_directory = detail::CreateDirectoryFunction {};
constexpr inline auto create_directories = detail::CreateDirectoriesFunction {};
constexpr inline auto remove = detail::RemoveFunction {};
constexpr inline auto remove_all = detail::RemoveAllFunction {};
}

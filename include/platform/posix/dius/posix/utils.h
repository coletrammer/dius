#pragma once

#include <di/vocab/pointer/box.h>

#include "di/container/string/string.h"
#include "di/container/string/zstring.h"
#include "di/container/tree/tree_map.h"
#include "di/container/tree/tree_set.h"

namespace dius::posix {
inline auto make_env(char** environ, di::TreeMap<di::TransparentString, di::TransparentString> const& extra_vars)
    -> di::Tuple<di::TreeSet<di::Box<di::TransparentString>>, di::Vector<char*>> {
    auto result = di::Vector<char*> {};
    for (auto* env_var = environ; *env_var; env_var++) {
        auto zstring = di::ZString(*env_var);
        auto it = di::find(zstring, '=');
        if (it == zstring.end()) {
            continue;
        }
        auto key = di::TransparentStringView(*env_var, &*it);
        if (extra_vars.contains(key)) {
            continue;
        }
        result.push_back(*env_var);
    }
    auto storage = di::TreeSet<di::Box<di::TransparentString>> {};
    for (auto const& [key, value] : extra_vars) {
        auto string = di::clone(key);
        string.push_back('=');
        string += value;
        auto [it, _] = storage.insert(di::make_box<di::TransparentString>(di::move(string)));
        result.push_back(const_cast<char*>((*it)->c_str()));
    }
    result.push_back(nullptr);
    return { di::move(storage), di::move(result) };
}

auto get_program_name() -> char const*;
auto get_env() -> char**;
}

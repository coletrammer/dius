#include "dius/posix/utils.h"
#include "dius/system/process.h"

namespace dius::system {
auto get_program_name() -> di::PathView {
    static auto program_name =
        di::ZCString(posix::get_program_name()) | di::to<di::Vector<char>>() | di::to<di::Path>();
    return program_name;
}

auto get_environment() -> di::TreeMap<di::TransparentString, di::TransparentString> const& {
    static auto env = [] {
        auto result = di::TreeMap<di::TransparentString, di::TransparentString> {};
        auto* c_env = posix::get_env();
        for (auto** env_var = c_env; *env_var != nullptr; env_var++) {
            auto zstring = di::ZString(*env_var);
            auto it = di::find(zstring, '=');
            auto key = di::TransparentStringView(*env_var, &*it).to_owned();
            if (it == zstring.end()) {
                result.insert_or_assign(di::move(key), ""_ts);
                continue;
            }
            ++it;
            auto value = di::TransparentStringView(&*it, &*di::next(it, zstring.end())).to_owned();
            result.insert_or_assign(di::move(key), di::move(value));
        }
        return result;
    }();
    return env;
}
}

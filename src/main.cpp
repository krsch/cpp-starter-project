#include "lib.hpp"
#include <charconv>
#include <cmath>
#include <fmt/core.h>
#include <optional>
#include <string_view>
#include <variant>

auto safe_sqrt(float x) noexcept -> std::optional<float> {
    if (x < 0)
        return std::nullopt;
    return std::sqrt(x);
}

auto parse_str(std::string_view s) -> std::variant<int, std::string_view> {
    if (auto start = s.find('"'); start != s.npos)
        return s.substr(start + 1, s.find('"', start + 1) - start - 1);
    int result;
    std::from_chars(s.data(), s.data() + s.size(), result);
    return result;
}

int main() {
    const auto arg = -5.F;
    if (auto res = safe_sqrt(arg))
        fmt::print("sqrt({}) = {}\n", arg, *res);
    else
        fmt::print("sqrt({}) is undefined\n", arg);
    auto res2 = safe_sqrt(arg).value_or(0);
    fmt::print("sqrt({}) or 0 = {}\n", arg, res2);

    auto p1 = parse_str("\"str1\"");
    if (int *ptr = std::get_if<int>(&p1))
        fmt::print("parsed int {}\n", *ptr);
    else if (auto *str = std::get_if<std::string_view>(&p1))
        fmt::print("parsed str {}\n", *str);
    auto visitor = [](auto &&value) { fmt::print("parsed {}\n", value); };
    std::visit(visitor, parse_str("123"));
    if (int *ptr = std::get_if<int>(&p1))
        visitor(*ptr);
    else if (auto *str = std::get_if<std::string_view>(&p1))
        visitor(*str);
    return 0;
}
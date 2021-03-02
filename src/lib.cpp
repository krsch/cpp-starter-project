#include "lib.hpp"
#include <algorithm>
#include <locale>
#include <string_view>

int not_random() { return 3; }

std::locale loc{""};
words_iterator::words_iterator(std::string_view s) : str(s) { normalize(); }
auto words_iterator::normalize() -> void {
    auto alpha = std::find_if(str.begin(), str.end(), isalpha);
    str.remove_prefix(size_t(alpha - str.begin()));
    auto nonalpha = std::find_if_not(str.begin(), str.end(), isalpha);
    length = size_t(nonalpha - str.begin());
}
auto words_iterator::isalpha(char c) -> bool { return std::isalpha(c, loc); }

auto words_iterator::operator*() const -> std::string_view {
    return str.substr(0, length);
}

auto words_iterator::operator++() -> words_iterator & {
    str.remove_prefix(length);
    normalize();
    return *this;
}

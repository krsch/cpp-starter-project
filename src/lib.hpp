#pragma once
#include <string_view>

extern int not_random();
struct words_iterator {
    std::string_view str;
    size_t length;
    words_iterator(std::string_view str);
    auto normalize() -> void;

    auto operator==(words_iterator const &other) const {
        return str.data() == other.str.data() && str.size() == other.str.size();
    }
    auto operator!=(words_iterator const &other) const {
        return !(*this == other);
    }

    static auto isalpha(char c) -> bool;
    auto operator*() const -> std::string_view;
    auto operator++() -> words_iterator &;
    auto operator++(int) -> words_iterator {
        auto old = *this;
        ++*this;
        return old;
    }
    auto operator->() const { return **this; }
};

struct words_range {
    std::string_view str;
    auto begin() const { return words_iterator{str}; }
    auto end() const { return words_iterator{str.substr(str.size())}; }
};
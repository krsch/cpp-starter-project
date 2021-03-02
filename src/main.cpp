#include "lib.hpp"
#include <initializer_list>
#include <iostream>
#include <memory>
#include <string_view>
#include <algorithm>
#include <cctype>

struct ListNode {
    int value;
    std::unique_ptr<ListNode> next;
    ListNode *prev = nullptr;
    ListNode(int value) : value(value) {}
};

struct List {
    std::unique_ptr<ListNode> first;
    List(std::initializer_list<int> list) {
        if (list.size() == 0)
            return;
        auto it = list.begin();
        first = std::make_unique<ListNode>(*it);
        auto node = first.get();
        ++it;
        while (it != list.end()) {
            node->next = std::make_unique<ListNode>(*it);
            node->next->prev = node;
            node = node->next.get();
            ++it;
        }
    }

    struct iterator {
        ListNode *node;

        auto operator==(iterator const &other) const {
            return node == other.node;
        }
        auto operator!=(iterator const &other) const {
            return node != other.node;
        }
        auto operator++() -> iterator & { // ++a
            node = node->next.get();
            return *this;
        }
        auto operator++(int) -> iterator { // a++
            auto *cur = node;
            node = node->next.get();
            return iterator{cur};
        }
        auto operator*() const { return node->value; }
        auto operator->() const { return &node->value; }
    };

    auto begin() { return iterator{first.get()}; }
    auto end() const { return iterator{nullptr}; }
};

struct words_iterator {
    std::string_view str;

    auto operator==(words_iterator const &other) const {
        return str == other.str;
    }
    auto operator!=(words_iterator const &other) const {
        return str != other.str;
    }
    auto operator*() const {
        auto it = std::find_if(str.begin(), str.end(),
                               [](char c) { return std::isalpha(c) == 0; });
        return str.substr(0, it - str.begin());
    }
    auto operator++() -> words_iterator&{
        auto nonalpha = std::find_if(str.begin(), str.end(), [](char c) {
            return std::isalpha(c) == 0;
        });
        auto alpha = std::find_if(nonalpha, str.end(), [](char c) {
            return std::isalpha(c) != 0;
        });
        str.remove_prefix(alpha - str.begin());
        return *this;
    }
};

struct words_range {
    std::string_view str;
    auto begin() const { return words_iterator{str}; }
    auto end() const { return words_iterator{str.substr(str.size())}; }
};

int main() {
    auto mylist = List{1, 2, 3, 4};
    for (auto value : mylist)
        std::cout << value << ", ";
    std::cout << "\n";
    using namespace std::literals;
    auto str = "hello world!"s;
    for (auto word : words_range{str})
        std::cout << word << ", ";
    std::cout << "\n";
    return 0;
}
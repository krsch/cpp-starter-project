#include "lib.hpp"
#include <algorithm>
#include <cctype>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <string_view>
#include <fmt/ranges.h>

struct ListNode {
    int value;
    std::unique_ptr<ListNode> next;
    ListNode *prev = nullptr;
    ListNode(int value) : value(value) {}
};

struct List {
    std::unique_ptr<ListNode> first;
    ListNode *last = nullptr;
    List(std::initializer_list<int> list) {
        if (list.size() == 0)
            return;
        auto it = list.begin();
        first = std::make_unique<ListNode>(*it);
        last = first.get();
        ++it;
        while (it != list.end()) {
            last->next = std::make_unique<ListNode>(*it);
            last->next->prev = last;
            last = last->next.get();
            ++it;
        }
    }

    struct iterator : std::iterator<std::bidirectional_iterator_tag, int> {
        ListNode *node;
        ListNode *prev;

        auto operator==(iterator const &other) const {
            return node == other.node;
        }
        auto operator!=(iterator const &other) const {
            return node != other.node;
        }
        auto operator++() -> iterator & { // ++a
            prev = node;
            node = node->next.get();
            return *this;
        }
        auto operator++(int) -> iterator { // a++
            auto *cur = node;
            node = node->next.get();
            return iterator{{}, cur, cur->prev};
        }
        auto operator--() -> iterator & { // --a
            node = prev;
            prev = node->prev;
            return *this;
        }
        auto operator--(int) -> iterator { // a--
            auto *cur = node;
            node = prev;
            prev = node->prev;
            return iterator{{}, cur, cur->prev};
        }
        auto operator*() const -> auto & { return node->value; }
        auto operator->() const { return &node->value; }
    };

    auto begin() const { return iterator{{}, first.get(), nullptr}; }
    auto end() const { return iterator{{}, nullptr, last}; }
};

int main() {
    auto mylist = List{1, 2, 3, 4};
    for (auto value : mylist)
        std::cout << value << ", ";
    std::cout << "\n";
    std::reverse(mylist.begin(), mylist.end());
    fmt::print("reversed: {}\n", mylist);
    using namespace std::literals;
    auto str = "hello world!"s;
    for (auto word : words_range{str})
        std::cout << word << ", ";
    std::cout << "\n";
    return 0;
}

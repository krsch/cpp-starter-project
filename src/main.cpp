#include "lib.hpp"
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fmt/ostream.h>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

/*
@dataclass
class List1:
    value: int
    next: 'List1' = None
    def __init__(self, v):
        self.value = v
*/
struct List1 {
    int value;
    std::shared_ptr<List1> next /* = nullptr */;
    List1(int v) { value = v; }
};
auto print(List1 const &list) -> void {
    fmt::print("{}{}", list.value, (list.next ? ", " : "\n"));
    // cond ? expr1 : expr2 это как в python было expr1 if cond else expr2
    if (list.next)
        print(*list.next);
}
auto step1() -> void {
    print(3);
    print(List1{3}); // то же самое
}

struct List2 {
    int value;
    std::shared_ptr<List1> next /* = nullptr */;
    explicit List2(int v) { value = v; }
};
auto print2(List2 const &list) -> void {
    fmt::print("{}{}", list.value, (list.next ? ", " : "\n"));
    // cond ? expr1 : expr2 это как в python было expr1 if cond else expr2
    if (list.next)
        print(*list.next);
}
auto step2() {
    // print2(3); // ERROR! потому что explicit
    print2(List2{3}); // то же самое
}

struct Stack {
    static const int max_number_of_elements = 32;
    // Stack::max_number_of_elements == 32
    std::array<int, max_number_of_elements> elements;
    size_t top = 0;

    auto push_back(int value) {
        elements[top] = value;
        ++top;
    }

    auto pop_back() {
        --top;
        return elements[top];
    }

    Stack() = default;
    // ^ пусть компилятор сам этот конструктор напишет, он умеет
    Stack(std::initializer_list<int> list) {
        for (auto elem : list)
            push_back(elem);
    }
};
std::ostream &operator<<(std::ostream &stream, Stack const &stack) {
    stream << "Stack{";
    for (size_t i = 0; i < stack.top; ++i)
        stream << i << (i == stack.top - 1 ? "" : ", ");
    stream << "}";
    return stream;
}
auto step3() {
    auto s1 = Stack();
    auto s2 = Stack{1, 2, 3};
    // Если компилятор видит '{', он ищет конструктор. принимающий
    // std::initializer_list. Если он есть, он и вызывается. Если его нет,
    // элементы в {} рассматриваются как отдельные аргументы конструктора
    std::cout << s2 << "\n";
    fmt::print("{}\n", s1);
}

int main() {
    std::cout << fmt::format("not_random number is {0:04}\n", not_random());
    fmt::print("Another string and a vector {}\n", std::vector{1, 2, 3, 4});
    step3();
    return 0;
}
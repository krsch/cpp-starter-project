#include "lib.hpp"
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <iostream>
#include <vector>

int main() {
    std::cout << fmt::format("not_random number is {0:04}\n", not_random());
    fmt::print("Another string and a vector {}\n", std::vector{1, 2, 3, 4});

    return 0;
}
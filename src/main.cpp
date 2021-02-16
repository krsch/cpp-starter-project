#include "lib.hpp"
#include <fmt/core.h>

int main() {
    for (auto length : {10, 100, 1000})
        fmt::print("Probability of orthogonality on length {} is {}\n", length,
                   orthogonal_probability(size_t(length)));
    for (auto length : {10, 100, 1000, 10000})
        fmt::print("Probability of almost orthogonality on length {} is {}\n",
                   length, almost_orthogonal_probability(size_t(length), 0.1));
}
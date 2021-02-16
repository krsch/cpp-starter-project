#include "lib.hpp"
#include <random>
#include <vector>

int not_random() { return 3; }

auto is_orthogonal(std::vector<bool> const &a,
                   std::vector<bool> const &b) noexcept -> bool {
    if (a.size() != b.size())
        return false;
    bool sum = true;
    for (size_t i = 0; i < a.size(); ++i)
        sum = sum != (a[i] && b[i]); // != - xor, && - and
    return sum;
}

auto orthogonal_probability(size_t n, double p) noexcept -> double {
    auto a = std::vector<bool>(n); // vector длины n из false
    auto b = std::vector<bool>(n);
    const int iterations = 1000;
    int orthogonal_count = 0;
    auto rng = std::default_random_engine();
    auto dist = std::bernoulli_distribution(p);
    for (int i = 0; i < iterations; ++i) {
        for (auto &&elem : a)
            elem = dist(rng);
        for (auto &&elem : b)
            elem = dist(rng);
        orthogonal_count += static_cast<int>(is_orthogonal(a, b));
        // static_cast<int>(...) - это как int(...)
    }
    return double(orthogonal_count) / iterations;
}

auto is_orthogonal(std::vector<double> const &a, std::vector<double> const &b,
                   double precision) noexcept -> bool {
    if (a.size() != b.size())
        return false;
    double sum = 0;
    for (size_t i = 0; i < a.size(); ++i)
        sum += a[i] * b[i];
    double sum_a = 0;
    for (auto elem : a)
        sum_a += elem * elem;
    double sum_b = 0;
    for (auto elem : b)
        sum_b += elem * elem;
    return (sum / std::sqrt(sum_a * sum_b)) < precision;
}

auto almost_orthogonal_probability(size_t n, double precision) noexcept
    -> double {
    auto a = std::vector(n, 0.0); // vector длины n из 0.0
    auto b = std::vector(n, 0.0);
    const int iterations = 1000;
    int orthogonal_count = 0;
    auto rng = std::default_random_engine();
    auto dist = std::normal_distribution<>();
    for (int i = 0; i < iterations; ++i) {
        for (auto &&elem : a)
            elem = dist(rng);
        for (auto &&elem : b)
            elem = dist(rng);
        orthogonal_count += static_cast<int>(is_orthogonal(a, b, precision));
        // static_cast<int>(...) - это как int(...)
    }
    return double(orthogonal_count) / iterations;
}
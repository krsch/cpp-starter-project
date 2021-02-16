#include "lib.hpp"
#include <numeric>
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
    // double sum = std::inner_product(a.begin(), a.end(), b.begin(), 0.0);
    // double sum_a = std::inner_product(a.begin(), a.end(), a.begin(), 0.0);
    // double sum_b = std::inner_product(b.begin(), b.end(), b.begin(), 0.0);
    double sum = 0;
    double sum_a = 0;
    double sum_b = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += a[i] * b[i];
        sum_a += a[i] * a[i];
        sum_b += b[i] * b[i];
    }
    return std::abs(sum / std::sqrt(sum_a * sum_b)) < precision;
}

auto orthogonal_ratio(std::vector<std::vector<double>> const &matrix,
                      double precision) noexcept -> double {
    int orthogonal_count = 0;
    int count = 0; // n*(n-1)/2
    for (size_t i = 0; i < matrix.size(); ++i)
        for (size_t j = 0; j < i; ++j) {
            orthogonal_count +=
                int(is_orthogonal(matrix[i], matrix[j], precision));
            ++count;
        }
    return double(orthogonal_count) / count;
}

auto orthogonal_ratio2(std::vector<std::vector<double>> const &matrix,
                       double precision) noexcept -> double {
    int orthogonal_count = 0;
    int count = 0; // n*(n-1)/2
    auto norm = std::vector(matrix.size(), 0.0);
    for (size_t r = 0; r < matrix.size(); ++r)
        norm[r] = std::sqrt(std::inner_product(
            matrix[r].begin(), matrix[r].end(), matrix[r].begin(), 0.0));
    for (size_t i = 0; i < matrix.size(); ++i)
        for (size_t j = 0; j < i; ++j) {
            bool orth =
                std::abs(std::inner_product(matrix[i].begin(), matrix[i].end(),
                                            matrix[j].begin(), 0.0) /
                         norm[i] / norm[j]) < precision;
            orthogonal_count += int(orth);
            ++count;
        }
    return double(orthogonal_count) / count;
}

auto almost_orthogonal_probability(size_t n, double precision) noexcept
    -> double {
    auto a = std::vector(n, 0.0); // vector длины n из 0.0
    auto b = std::vector(n, 0.0);
    const size_t iterations = n * (n - 1) / 2;
    int orthogonal_count = 0;
    auto rng = std::default_random_engine();
    auto dist = std::normal_distribution<>();
    for (size_t i = 0; i < iterations; ++i) {
        for (auto &&elem : a)
            elem = dist(rng);
        for (auto &&elem : b)
            elem = dist(rng);
        orthogonal_count += static_cast<int>(is_orthogonal(a, b, precision));
        // static_cast<int>(...) - это как int(...)
    }
    return double(orthogonal_count) / double(iterations);
}

auto almost_orthogonal_probability_matrix(size_t n, double precision) noexcept
    -> double {
    auto a = std::vector(n, std::vector(n, 0.0));
    const int iterations = 1;
    double orthogonal_count = 0;
    auto rng = std::default_random_engine();
    auto dist = std::normal_distribution<>();
    for (int i = 0; i < iterations; ++i) {
        for (auto &&row : a)
            for (auto &&elem : row)
                elem = dist(rng);
        orthogonal_count += orthogonal_ratio(a, precision);
        // static_cast<int>(...) - это как int(...)
    }
    return orthogonal_count / iterations;
}

auto almost_orthogonal_probability_matrix2(size_t n, double precision) noexcept
    -> double {
    auto a = std::vector(n, std::vector(n, 0.0));
    const int iterations = 1;
    double orthogonal_count = 0;
    auto rng = std::default_random_engine();
    auto dist = std::normal_distribution<>();
    for (int i = 0; i < iterations; ++i) {
        for (auto &&row : a)
            for (auto &&elem : row)
                elem = dist(rng);
        orthogonal_count += orthogonal_ratio2(a, precision);
        // static_cast<int>(...) - это как int(...)
    }
    return orthogonal_count / iterations;
}
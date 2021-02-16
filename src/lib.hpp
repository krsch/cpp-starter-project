#pragma once
#include <vector>

extern int not_random();

extern auto is_orthogonal(std::vector<bool> const &a,
                          std::vector<bool> const &b) noexcept -> bool;
// NOLINTNEXTLINE(readability-magic-numbers)
extern auto orthogonal_probability(size_t n, double p = 0.5) noexcept -> double;
extern auto is_orthogonal(std::vector<double> const &a,
                          std::vector<double> const &b,
                          // NOLINTNEXTLINE(readability-magic-numbers)
                          double precision = 1e-4) noexcept -> bool;
extern auto
almost_orthogonal_probability(size_t n,
                              // NOLINTNEXTLINE(readability-magic-numbers)
                              double precision = 1e-4) noexcept -> double;
extern auto orthogonal_ratio(std::vector<std::vector<double>> const &matrix,
                             double precision) noexcept -> double;

extern auto almost_orthogonal_probability_matrix(size_t n,
                                                 double precision) noexcept
    -> double;
extern auto almost_orthogonal_probability_matrix2(size_t n,
                                                  double precision) noexcept
    -> double;

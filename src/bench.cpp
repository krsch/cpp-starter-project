#include "lib.hpp"
#include <benchmark/benchmark.h>
#include <random>

static void BM_probability(benchmark::State &state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        almost_orthogonal_probability(1000, 0.1);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_probability);

static void BM_orthogonal(benchmark::State &state) {
    // Perform setup here
    const size_t n = 1000;
    auto a = std::vector(n, 0.0); // vector длины n из 0.0
    auto rng = std::default_random_engine();
    auto dist = std::normal_distribution<float>();
    for (auto _ : state) {
        // This code gets timed
        for (auto &&elem : a)
            elem = dist(rng);
        benchmark::DoNotOptimize(is_orthogonal(a, a, 0.1));
    }
}
// Register the function as a benchmark
BENCHMARK(BM_orthogonal);

static void BM_random(benchmark::State &state) {
    // Perform setup here
    const size_t n = 1000;
    auto a = std::vector(n, 0.0); // vector длины n из 0.0
    auto rng = std::default_random_engine();
    auto dist = std::normal_distribution<float>();
    for (auto _ : state) {
        // This code gets timed
        for (auto &&elem : a)
            elem = dist(rng);
        benchmark::DoNotOptimize(a);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_random);
// Run the benchmark
BENCHMARK_MAIN();
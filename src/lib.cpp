#include "lib.hpp"

auto not_random() -> int { return 3; }
// def not_random() -> int: return 3

auto do_nothing() -> void {}
// или auto do_nothing() {}

auto sqr(double x) -> double { return x * x; }
// def sqr(x: double) -> double: return x * x
// def sqr(x): return x * x
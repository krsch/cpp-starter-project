#include "lib.hpp"
#include <doctest.h>

TEST_CASE("Something works") { REQUIRE(not_random() == not_random()); }
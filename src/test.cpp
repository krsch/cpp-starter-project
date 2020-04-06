#include "catch.hpp"
#include "lib.hpp"

TEST_CASE("Something works") { REQUIRE(not_random() == not_random()); }
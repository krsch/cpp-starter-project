#include "catch.hpp"
#include "lib.hpp"
#include <algorithm>

TEST_CASE("Something works") { REQUIRE(not_random() == not_random()); }

TEST_CASE("words_range") {
    using namespace std::literals;
    auto words = words_range{" hello world from me!"sv};
    auto words_list = {"hello"sv, "world"sv, "from"sv, "me"sv};
    auto [it, it_list] = std::mismatch(words.begin(), words.end(),
                                       words_list.begin(), words_list.end());
    REQUIRE(it == words.end());
    REQUIRE(it_list == words_list.end());
}
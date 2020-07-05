// Test bi-directional version of read-write hidden iterator
#include "indir.sub.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
using Catch::Matchers::Equals;

#include <map>
#include <string>

SCENARIO("Indirect map iterator", "[hiter]") {

  THEN("It should be default-constructable") {
    IterMapStrIndir empty;
  }

  GIVEN("An iterator for map<string, string>") {
    std::map<std::string, std::string> m {{"aa", "bb"}, {"cc", "dd"}, {"", "zzz"}};
    THEN("It simply works") {
      auto itr = m.begin(), itrEnd = m.end();
      IterMapStrIndir b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        REQUIRE_THAT(b->first, Equals(itr->first.c_str()));
        REQUIRE_THAT(b->second, Equals(itr->second.c_str()));
        REQUIRE(b != e);
      }
      REQUIRE(b == e);
    }
  }
} // end read-write scenario

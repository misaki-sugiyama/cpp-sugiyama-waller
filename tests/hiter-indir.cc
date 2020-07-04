// Test bi-directional version of read-write hidden iterator
#include "hiter-indir.sub.h"
#include <catch2/catch_test_macros.hpp>

#include <map>
#include <string>
#include <cstring> // for strcmp

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
        REQUIRE(strcmp(b->first, itr->first.c_str()) == 0);
        REQUIRE(strcmp(b->second, itr->second.c_str()) == 0);
        REQUIRE(b != e);
      }
      REQUIRE(b == e);
    }
  }
} // end read-write scenario

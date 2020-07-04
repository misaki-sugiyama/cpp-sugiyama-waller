// Test direct version of read-only hidden iterator
#include "direct.sub.h"
#include <catch2/catch_test_macros.hpp>

#include <forward_list>

SCENARIO("Straightforward iterator", "[hiter]") {

  THEN("It should be default-constructable") {
    IterSListInt empty;
  }

  GIVEN("An iterator for forward_list<int>") {
    const std::forward_list<int> s {9,3,7};
    THEN("It simply works") {
      auto itr = s.begin(), itrEnd = s.end();
      IterSListInt b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        REQUIRE(*b == *itr);
        REQUIRE(b != e);
      }
      REQUIRE(b == e);
    }
  }
} // end straightforward scenario

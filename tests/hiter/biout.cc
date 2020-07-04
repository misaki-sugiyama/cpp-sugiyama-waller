// Test bi-directional version of read-write hidden iterator
#include "biout.sub.h"
#include <catch2/catch_test_macros.hpp>

#include <list>

SCENARIO("Bi-directional read-write iterator", "[hiter]") {

  THEN("It should be default-constructable") {
    IterBListIntOut empty;
  }

  GIVEN("An iterator for list<int>") {
    const std::list<int> s {9,3,7};
    THEN("It simply works") {
      auto itr = s.begin(), itrEnd = s.end();
      IterBListIntOut b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        REQUIRE(*b == *itr);
        REQUIRE(b != e);
      }
      REQUIRE(b == e);
    }

    THEN("It can write") {
      auto itr = s.begin();
      IterBListIntOut b {&itr};
      *b = 20;
      REQUIRE(*s.begin() == 20);
    }
  }
} // end read-write scenario

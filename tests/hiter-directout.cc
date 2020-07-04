// Test direct version of read-write hidden iterator
#include "hiter-directout.sub.h"
#include <catch2/catch_test_macros.hpp>

#include <forward_list>

SCENARIO("Read-write iterator", "[hiter]") {

  THEN("It should be default-constructable") {
    IterSListIntOut empty;
  }

  GIVEN("An iterator for forward_list<int>") {
    const std::forward_list<int> s {9,3,7};
    THEN("It simply works") {
      auto itr = s.begin(), itrEnd = s.end();
      IterSListIntOut b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        REQUIRE(*b == *itr);
        REQUIRE(b != e);
      }
      REQUIRE(b == e);
    }

    THEN("It can write") {
      auto itr = s.begin();
      IterSListIntOut b {&itr};
      *b = 20;
      REQUIRE(*s.begin() == 20);
    }
  }
} // end read-write scenario

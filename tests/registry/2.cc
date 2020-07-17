// 2-parameter registered things
#include "2.sub.class.h"
#include "sugiyama/exception-registry.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
using Catch::Matchers::Equals;

SCENARIO("2-parameter registry", "[reg]") {
  const auto& reg = RegSubject2::obj();

  GIVEN("One registered class") {
    THEN("It can be manifested correctly") {
      auto p1 = reg.make("Subject2a", 50, 80);
      REQUIRE(p1->get() == 130);
    }
  }

} // end 2 parameter scenario

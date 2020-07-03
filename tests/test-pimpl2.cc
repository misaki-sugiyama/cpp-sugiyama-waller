// Simple pimpl object with two parameters - subject pimpl2
#include "subj-pimpl2.h"
#include <catch2/catch_test_macros.hpp>

// === two parameters === //

SCENARIO("PImpl object with two parameters", "[pimpl]") {

  GIVEN("A class with two-param pimpl") {
    Test2 obj {300, 400};
    THEN("It simply works") {
      REQUIRE(obj.run() == 700);
    }
    THEN("The const qualifier is not discarded") {
      REQUIRE(obj.runconst() == 701);
    }
  } // end basic test

} // end 2 parameter scenario

// Test bi-directional version of read-write hidden iterator
#include "sugiyama/exception.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
using Catch::Matchers::Equals;

using sugiyama::exception;

SCENARIO("exception class", "[exception]") {

  THEN("It should be default-constructable") {
    exception empty;
  }

  THEN("It should be able to store a string message") {
    exception eStr {"ABC CDE"};
    REQUIRE_THAT(eStr.what(), Equals("ABC CDE"));
  }

  THEN("It should be able to store an integer") {
    exception eInt {16777216};
    REQUIRE_THAT(eInt.what(), Equals("16777216"));
  }

  THEN("It should be able to store a floating point number") {
    exception eDouble {3.1416};
    REQUIRE_THAT(eDouble.what(), Equals("3.141600"));
  }

} // end exception test

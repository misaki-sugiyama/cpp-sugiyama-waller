// 0-parameter registered things
#include "0.sub.class.h"
#include "sugiyama/exception-registry.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
using Catch::Matchers::Equals;

SCENARIO("0-parameter registry", "[reg]") {
  const auto& reg = RegSubject0::obj();

  GIVEN("The registry itself") {
    THEN("It has right number of things") {
      REQUIRE(reg.size() == 2);
    }
    THEN("It can distinguish between things exist and not") {
      REQUIRE(reg.has("Subject0a"));
      REQUIRE(reg.has("Subject0b"));
      REQUIRE(!reg.has("Subject0c"));
    }
  }

  GIVEN("Registry iterators") {
    THEN("It can correctly read the name and description") {
      auto it = reg.begin();
      REQUIRE_THAT(it->first, Equals("Subject0a"));
      REQUIRE_THAT(it->second, Equals("Description0a"));
      ++it;
      REQUIRE_THAT(it->first, Equals("Subject0b"));
      REQUIRE_THAT(it->second, Equals("Description0b"));
      ++it;
      REQUIRE(it == reg.end()); // the end of the iteration
    }
  }

  GIVEN("Two registered classes") {
    THEN("They can be manifested correctly") {
      auto p1 = reg.make("Subject0a");
      REQUIRE(p1->get() == 1);
      auto p2 = reg.make("Subject0b");
      REQUIRE(p2->get() == 2);
    }

    THEN("We can read their descriptions") {
      REQUIRE_THAT(reg.getDesc("Subject0a"), Equals("Description0a"));
      REQUIRE_THAT(reg.getDesc("Subject0b"), Equals("Description0b"));
    }

    WHEN("Asked to deal with a non-existent class") {
      THEN("It should throw") {
        REQUIRE_THROWS_AS(
            reg.make("Subject0c"),
            ::sugiyama::ExceptionRegistryOutOfRange
            );
        REQUIRE_THROWS_AS(
            reg.getDesc("Subject0c"),
            ::sugiyama::ExceptionRegistryOutOfRange
            );
      }
    }
  }

} // end 0 parameter scenario


SCENARIO("Wrong usage of the registry", "[reg]") {
  auto& reg = RegSubject0::obj();

  WHEN("We register an null function pointer") {
    THEN("It should throw") {
      REQUIRE_THROWS_AS(
          reg.addEntry("name-doesnt-matter", "desc", nullptr),
          ::sugiyama::ExceptionRegistryAddNull
          );
    }
  } // end null

  WHEN("We register a duplicated name") {
    THEN("It should throw") {
      REQUIRE_THROWS_AS(
          reg.addEntry("Subject0a", "desc",
            []()->Pointer<ISubject0>{return nullptr;}
            ),
          ::sugiyama::ExceptionRegistryAddDup
          );
    }
  } // end duplicate

} // end wrong usage

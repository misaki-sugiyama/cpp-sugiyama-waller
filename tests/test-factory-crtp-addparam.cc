// Tests for CRTP wrapper with additional template parameters
#include "sugiyama/factory-crtp.h"
#include <catch2/catch_test_macros.hpp>

template <class Derived, typename T>
class Func10 : public sugiyama::FacCRTP<Func10, Derived, T> {
public:
  T func10() {
    return this->derived().i+10;
  }
};

class Final1 : public Func10<Final1, int> {
public:
  int i {100};
};

SCENARIO("CRTP wrapper with additional types", "[crtp]") {
  Final1 obj;
  THEN("It should just work") {
    REQUIRE(obj.func10() == 110);
  }
}

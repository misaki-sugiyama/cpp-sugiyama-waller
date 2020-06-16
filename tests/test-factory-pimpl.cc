#include "sugiyama/factory-pimpl.h"
#include "sugiyama/factory-pimpl-inl.h"
#include <catch2/catch_test_macros.hpp>

// === no parameters === //

class Test0 {
private:
  class Impl;
  sugiyama::FacPImpl<Impl> pimpl;
public:
  int run();
};

class Test0::Impl {
public:
  int a {179};
  int run() {
    return a;
  }
};

int Test0::run() {
  return pimpl->run();
}

SCENARIO("PImpl object without parameters", "[pimpl]") {

  GIVEN("A class with zero-param pimpl") {
    Test0 obj;
    THEN("It simply works") {
      REQUIRE(obj.run() == 179);
    }
  }
} // end 0 parameter scenario


// === two parameters === //

class Test2 {
private:
  class Impl;
  sugiyama::FacPImpl<Impl> pimpl;
public:
  Test2();
  Test2(int a, int b);
  int run();
  int runconst() const;
};

class Test2::Impl {
public:
  Impl(int a, int b) : a(a+b) {}
  int a;
  int run() {
    return a;
  }
  int runconst() const {
    return a+1;
  }
};

Test2::Test2() : pimpl(999, 999) {}
Test2::Test2(int a, int b) : pimpl(a, b) {}

int Test2::run() {
  return pimpl->run();
}
int Test2::runconst() const {
  return pimpl->runconst();
}

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

  GIVEN("A class that should be copyable") {
    Test2 obj {300, 400};
    THEN("The pimpl object can be copied") {
      Test2 objCopyCtor(obj);
      REQUIRE(objCopyCtor.run() == 700);
      Test2 objCopyAssign;
      objCopyAssign = obj;
      REQUIRE(objCopyAssign.run() == 700);
    }
  } // end copy test

  GIVEN("A class that should be movable") {
    Test2 obj {300, 400};
    Test2 obj2 {300, 400};
    THEN("The pimpl object can be copied") {
      Test2 objMoveCtor(std::move(obj));
      REQUIRE(objMoveCtor.run() == 700);
      Test2 objMoveAssign;
      objMoveAssign = std::move(obj2);
      REQUIRE(objMoveAssign.run() == 700);
    }
  } // end copy test

} // end 2 parameter scenario

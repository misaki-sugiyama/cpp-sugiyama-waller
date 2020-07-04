// Simple pimpl object which can be copied or moved
#include "cpmv.sub.h"
#include <catch2/catch_test_macros.hpp>

using testclass::TestCpMv;

SCENARIO("PImpl object which can be copied or moved", "[pimpl]") {

  GIVEN("A class that should be copyable") {
    TestCpMv obj {300};
    THEN("The pimpl object can be copied with copy constructor") {
      TestCpMv objCopyCtor(obj);
      REQUIRE(*objCopyCtor.getPtr() == *obj.getPtr());
      REQUIRE(objCopyCtor.getPtr() != obj.getPtr());
    }
    THEN("The pimpl object can be copied with copy assign") {
      TestCpMv objCopyAssign;
      objCopyAssign = obj;
      REQUIRE(*objCopyAssign.getPtr() == *obj.getPtr());
      REQUIRE(objCopyAssign.getPtr() != obj.getPtr());
    }
  } // end copy test

  GIVEN("A class that should be moveable") {
    const int ans = 300;
    TestCpMv obj {ans};
    const int* pAns = obj.getPtr();
    THEN("The pimpl object can be moved with move constructor") {
      TestCpMv objMoveCtor(std::move(obj));
      REQUIRE(*objMoveCtor.getPtr() == ans);
      REQUIRE(objMoveCtor.getPtr() == pAns);
    }
    THEN("The pimpl object can be moved with move assign") {
      TestCpMv objMoveAssign;
      objMoveAssign = std::move(obj);
      REQUIRE(*objMoveAssign.getPtr() == ans);
      REQUIRE(objMoveAssign.getPtr() == pAns);
    }
  } // end move test

} // end 2 parameter scenario

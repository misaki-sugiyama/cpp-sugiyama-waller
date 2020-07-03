// Tests for basic CRTP wrapper
#include "sugiyama/crtp.h"
#include <catch2/catch_test_macros.hpp>

template <class Derived>
class Func1 : public sugiyama::CRTPHelper<Func1, Derived> {
public:
  int func1() {
    return this->derived().i+1;
  }
};

template <class Derived>
class Func2 : public sugiyama::CRTPHelper<Func2, Derived> {
public:
  int func2() {
    return this->derived().i+2;
  }
};

class Final : public Func1<Final>, public Func2<Final> {
public:
  int i {100};
};

template<template<typename> class... CRTPs>
class FinalPackedPre : public CRTPs<FinalPackedPre<CRTPs...>>... {
public:
  int i {200};
};
using FinalPacked = FinalPackedPre<Func1, Func2>;

SCENARIO("CRTP wrapper", "[crtp]") {

  Final obj;
  THEN("It should just work") {
    REQUIRE(obj.func1() == 101);
    REQUIRE(obj.func2() == 102);
  }

  WHEN("Using the more complicated syntax") {
    FinalPacked obj2;
    THEN("It should also just work") {
      REQUIRE(obj2.func1() == 201);
      REQUIRE(obj2.func2() == 202);
    }
  }

}

#pragma once
#include "sugiyama/itf-registrable.h"

class ISubject2 : public sugiyama::IRegistrable {
public:
  int a, b;
  ISubject2(int a, int b) : a{a}, b{b} {};
  virtual int get() = 0;
};

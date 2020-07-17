#pragma once
#include "sugiyama/itf-registrable.h"

class ISubject0 : public sugiyama::IRegistrable {
public:
  using IRegistrable::IRegistrable;
  virtual int get() = 0;
};

#pragma once
#include "sugiyama/pimpl.h"
#include "sugiyama/ro5.h"

namespace testclass {

  class TestCpMv {
  private:
    class Impl;
    sugiyama::PImpl<Impl> pimpl;
  public:
    TestCpMv();
    TestCpMv(int a);

    SUGIYAMA_RO5_DEC(TestCpMv);

    int* getPtr();
  };

}

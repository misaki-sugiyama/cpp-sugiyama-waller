#pragma once
#include "sugiyama/pimpl.h"

namespace testclass {

  class TestCpMv {
  private:
    class Impl;
    sugiyama::PImpl<Impl> pimpl;
  public:
    TestCpMv();
    TestCpMv(int a);

    ~TestCpMv();
    TestCpMv(TestCpMv&& rhs) noexcept;
    TestCpMv& operator=(TestCpMv&& rhs) noexcept;
    TestCpMv(const TestCpMv& rhs);
    TestCpMv& operator=(const TestCpMv& rhs);

    int* getPtr();
  };

}

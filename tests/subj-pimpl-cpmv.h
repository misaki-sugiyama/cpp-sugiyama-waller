#include "sugiyama/factory-pimpl.h"

namespace testclass {

  class TestCpMv {
  private:
    class Impl;
    sugiyama::FacPImpl<Impl> pimpl;
  public:
    TestCpMv();
    TestCpMv(int a);

    SUGIYAMA_PIMPL_CPMV_DEC(TestCpMv);

    int* getPtr();
  };

}

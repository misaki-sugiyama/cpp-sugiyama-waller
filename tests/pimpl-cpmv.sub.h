#include "sugiyama/pimpl.h"

namespace testclass {

  class TestCpMv {
  private:
    class Impl;
    sugiyama::PImpl<Impl> pimpl;
  public:
    TestCpMv();
    TestCpMv(int a);

    SUGIYAMA_PIMPL_CPMV_DEC(TestCpMv);

    int* getPtr();
  };

}

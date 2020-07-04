#include "2.sub.h"
#include "sugiyama/pimpl-inl.h"

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

Test2::~Test2() = default;
Test2::Test2() : pimpl(999, 999) {}
Test2::Test2(int a, int b) : pimpl(a, b) {}

int Test2::run() {
  return pimpl->run();
}

int Test2::runconst() const {
  return pimpl->runconst();
}

SUGIYAMA_PIMPL_INST(Test2::Impl);

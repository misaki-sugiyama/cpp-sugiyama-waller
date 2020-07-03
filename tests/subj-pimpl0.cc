#include "sugiyama/factory-pimpl-inl.h"
#include "subj-pimpl0.h"

class Test0::Impl {
public:
  int a {179};
  int run() {
    return a;
  }
};

Test0::~Test0() = default;
Test0::Test0() = default;

int Test0::run() {
  return pimpl->run();
}

SUGIYAMA_PIMPL_INST(Test0::Impl);

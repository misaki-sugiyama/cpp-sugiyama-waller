#include "cpmv.sub.h"
#include "sugiyama/pimpl-inl.h"

#include <vector>

class testclass::TestCpMv::Impl {
private:
  std::vector<int> m_vec;
public:
  // No destructor/copy/move, copy and move can be automatically generated
  Impl(int a) {
    m_vec.push_back(a);
  }

  int* getPtr() {
    return &m_vec[0];
  }
};

testclass::TestCpMv::TestCpMv() : pimpl(0) {}
testclass::TestCpMv::TestCpMv(int a) : pimpl(a) {}

testclass::TestCpMv::~TestCpMv() = default;
testclass::TestCpMv::TestCpMv(testclass::TestCpMv&& rhs) noexcept = default;
testclass::TestCpMv& testclass::TestCpMv::operator=(testclass::TestCpMv&& rhs) noexcept = default;
testclass::TestCpMv::TestCpMv(const testclass::TestCpMv& rhs) = default;
testclass::TestCpMv& testclass::TestCpMv::operator=(const testclass::TestCpMv& rhs) = default;

int* testclass::TestCpMv::getPtr() {
  return pimpl->getPtr();
}

SUGIYAMA_PIMPL_INST(testclass::TestCpMv::Impl);

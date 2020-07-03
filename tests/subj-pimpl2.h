#include "sugiyama/factory-pimpl.h"

class Test2 {
private:
  class Impl;
  sugiyama::FacPImpl<Impl> pimpl;
public:
  Test2();
  Test2(int a, int b);
  ~Test2();
  int run();
  int runconst() const;
};

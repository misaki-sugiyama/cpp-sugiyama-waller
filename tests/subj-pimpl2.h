#include "sugiyama/pimpl.h"

class Test2 {
private:
  class Impl;
  sugiyama::PImpl<Impl> pimpl;
public:
  Test2();
  Test2(int a, int b);
  ~Test2();
  int run();
  int runconst() const;
};

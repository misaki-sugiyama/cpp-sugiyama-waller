#include "sugiyama/pimpl.h"

class Test0 {
private:
  class Impl;
  sugiyama::PImpl<Impl> pimpl;
public:
  Test0();
  ~Test0();
  int run();
};

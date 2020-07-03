#include "sugiyama/factory-pimpl.h"

class Test0 {
private:
  class Impl;
  sugiyama::FacPImpl<Impl> pimpl;
public:
  Test0();
  ~Test0();
  int run();
};


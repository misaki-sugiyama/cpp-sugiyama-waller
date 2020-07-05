// Just make sure this compiles
#include "sugiyama/uniq.h"

namespace {
  int __UNIQLOCALNAME__() { return 1; }
  int __UNIQLOCALNAME__() { return 2; }
  int __UNIQLOCALNAME__() { return 3; }
}

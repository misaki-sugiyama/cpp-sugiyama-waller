// The interface of registrable class
#pragma once
#include "sugiyama/ro5.h"

namespace sugiyama {
  class IRegistrable {
  public:
    IRegistrable();
    SUGIYAMA_RO5_DEC_V(IRegistrable);
  };
}

#define SUGIYAMA_NAME_DESC(n, d) \
  static constexpr const char* name {n}; \
  static constexpr const char* desc {d};

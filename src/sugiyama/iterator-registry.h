// The hidden iterator for registry info extraction
#pragma once

#include "sugiyama/factory-hiter.h"

#include <utility> // for pair

namespace sugiyama {

  class IterRegistry : public ::sugiyama::FacHiddenIterIndirect<IterRegistry, std::pair<const char*, const char*>> {
  public:
    using FacHiddenIter::FacHiddenIter;
    void fillCache();
  };

}

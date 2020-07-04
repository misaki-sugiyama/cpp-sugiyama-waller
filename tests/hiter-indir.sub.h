#pragma once
#include "sugiyama/factory-hiter.h"

#include <utility> // for pair

class IterMapStrIndir : public ::sugiyama::FacHiddenIterIndirect<IterMapStrIndir, std::pair<const char*, const char*>> {
public:
  using FacHiddenIter::FacHiddenIter;
  void fillCache();
};

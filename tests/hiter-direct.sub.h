#pragma once
#include "sugiyama/factory-hiter.h"

class IterSListInt : public ::sugiyama::FacHiddenIterDirect<IterSListInt, int> {
public:
  using FacHiddenIter::FacHiddenIter;
};

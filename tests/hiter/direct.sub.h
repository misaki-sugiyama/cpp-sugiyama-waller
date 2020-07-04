#pragma once
#include "sugiyama/factory-hiter.h"

class IterSListInt : public ::sugiyama::FacHiddenIterInput<IterSListInt, int> {
public:
  using FacHiddenIter::FacHiddenIter;
};

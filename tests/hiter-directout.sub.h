#pragma once
#include "sugiyama/factory-hiter.h"

class IterSListIntOut : public ::sugiyama::FacHiddenIterOutput<IterSListIntOut, int> {
public:
  using FacHiddenIter::FacHiddenIter;
};

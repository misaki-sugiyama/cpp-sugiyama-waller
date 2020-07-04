#pragma once
#include "sugiyama/factory-hiter.h"

class IterBListIntOut : public ::sugiyama::FacHiddenIterBiOutput<IterBListIntOut, int> {
public:
  using FacHiddenIter::FacHiddenIter;
};

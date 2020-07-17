#pragma once
#include "0.sub.reg.h"

class Subject0 : public ISubject0, public sugiyama::FacRegistryAssociator<RegSubject0> {
  using ISubject0::ISubject0;
};

#pragma once
#include "2.sub.reg.h"

class Subject2 : public ISubject2, public sugiyama::FacRegistryAssociator<RegSubject2> {
  using ISubject2::ISubject2;
};

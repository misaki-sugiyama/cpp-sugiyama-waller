#pragma once
#include "2.sub.itf.h"
#include "sugiyama/factory-registry.h"

class RegSubject2 : public sugiyama::FacRegistry<RegSubject2, ISubject2, int, int> {};

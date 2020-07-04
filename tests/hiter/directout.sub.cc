#include "directout.sub.h"
#include "sugiyama/factory-hiter-inl.h"

#include <forward_list>

SUGIYAMA_HITER_INST_OUTPUT(IterSListIntOut, int, std::forward_list<int>::iterator);

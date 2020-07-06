#include "sugiyama/iterator-registry.h"
#include "sugiyama/factory-hiter-inl.h"

#include <string>
#include <map>

using PairCsCs = std::pair<const char*, const char*>;
using MapSS = std::map<std::string, std::string>;
SUGIYAMA_HITER_INST_INDIRECT(sugiyama::IterRegistry, PairCsCs, MapSS::iterator);

namespace sugiyama {

  void IterRegistry::fillCache() {
    this->m_cache = std::pair((*pimpl)->first.c_str(), (*pimpl)->second.c_str());
  }

}

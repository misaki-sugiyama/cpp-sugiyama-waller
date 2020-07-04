#include "hiter-indir.sub.h"
#include "sugiyama/factory-hiter-inl.h"

#include <map>
#include <string>

using PairCsCs = std::pair<const char*, const char*>;
using MapSS = std::map<std::string, std::string>;
SUGIYAMA_HITER_INST_INDIRECT(IterMapStrIndir, PairCsCs, MapSS::iterator);

void IterMapStrIndir::fillCache() {
  this->m_cache = std::pair((*this->pimpl)->first.c_str(), (*this->pimpl)->second.c_str());
}

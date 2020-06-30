#include "sugiyama/factory-hiter.h"
#include "sugiyama/factory-hiter-inl.h"
#include <catch2/catch_test_macros.hpp>

#include <set>
#include <map>
#include <string>
#include <cstring> // strcmp

// === Direct version: the output type is exactly the type inside the container ===

// These are for the header
//class IterSetInt : public ::sugiyama::FacHiddenIter<int, IterSetInt> {
class IterSetInt : public ::sugiyama::FacHiddenIterDirect<IterSetInt, int> {
public:
  using FacHiddenIterDirect::FacHiddenIterDirect;
};

// These goes into implementation
template <>
class sugiyama::FacHiddenIterDirect<IterSetInt, int>::Impl : public ::sugiyama::FacHiddenIterImpl<std::set<int>::iterator> {
  using FacHiddenIterImpl::FacHiddenIterImpl;
};
template class ::sugiyama::FacHiddenIterDirect<IterSetInt, int>;

SCENARIO("Straightforward iterator", "[hiter]") {

  THEN("It should be default-constructable") {
    IterSetInt empty;
  }

  GIVEN("An iterator for set<int>") {
    const std::set<int> s {9,3,7};
    THEN("It simply works") {
      auto itrBegin = s.begin();
      auto itrEnd = s.end();
      IterSetInt b {&itrBegin};
      IterSetInt e {&itrEnd};
      REQUIRE(*b == 3);
      ++b;
      REQUIRE(*b == 7);
      ++b;
      REQUIRE(*b == 9);
      REQUIRE(b != e);
      ++b;
      REQUIRE(b == e);
    }
  }
} // end straightforward scenario

// === Indirect version: the output type need some conversion from the type inside the container ===

//// These are for the header
//class IterMapStr : public ::sugiyama::FacHiddenIter<std::pair<const char*, const char*>, IterMapStr> {
//public:
//  using FacHiddenIter::FacHiddenIter;
//  void fillCache();
//};

//// These goes into implementation
//template <>
//class sugiyama::FacHiddenIter<std::pair<const char*, const char*>, IterMapStr>::Impl : public ::sugiyama::FacHiddenIterImpl<std::pair<const char*, const char*>, std::map<std::string, std::string>::iterator> {
//  using FacHiddenIterImpl::FacHiddenIterImpl;
//};
//template class ::sugiyama::FacHiddenIter<std::pair<const char*, const char*>, IterMapStr>;

//void IterMapStr::fillCache() {
//  pimpl->m_cache = std::pair((*pimpl)->first.c_str(), (*pimpl)->second.c_str());
//}

//SCENARIO("Indirect iterator", "[hiter]") {

//  THEN("It should be default-constructable") {
//    IterMapStr empty;
//  }

//  GIVEN("An iterator for set<int>") {
//    std::map<std::string, std::string> m {{"aa", "bb"}, {"cc", "dd"}};
//    THEN("It simply works") {
//      auto itrBegin = m.begin();
//      auto itrEnd = m.end();
//      IterMapStr b {&itrBegin};
//      IterMapStr e {&itrEnd};
//      REQUIRE(strcmp(b->first, "aa") == 0);
//      REQUIRE(strcmp(b->second, "bb") == 0);
//      ++b;
//      REQUIRE(strcmp(b->first, "cc") == 0);
//      REQUIRE(strcmp(b->second, "dd") == 0);
//      REQUIRE(b != e);
//      ++b;
//      REQUIRE(b == e);
//    }
//  }
//} // end straightforward scenario

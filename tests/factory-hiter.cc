#include "sugiyama/factory-hiter.h"
#include "sugiyama/factory-hiter-inl.h"
#include <catch2/catch_test_macros.hpp>

#include <set>
#include <vector>
#include <map>
#include <string>
#include <cstring> // strcmp

// === Direct version: the output type is exactly the type inside the container ===

// These are for the header
class IterSetInt : public ::sugiyama::FacHiddenIterDirect<IterSetInt, int> {
public:
  using FacHiddenIterDirect::FacHiddenIterDirect;
};

// These goes into implementation
template <>
class sugiyama::FacHiddenIterDirect<IterSetInt, int>::Impl : public ::sugiyama::FacHiddenIterImpl<IterSetInt, std::set<int>::iterator> {
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
      auto itr = s.begin(), itrEnd = s.end();
      IterSetInt b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        REQUIRE(*b == *itr);
        REQUIRE(b != e);
      }
      REQUIRE(b == e);
    }
  }
} // end straightforward scenario

// === Direct version: Modifiable iterator ===

// These are for the header
class IterVecInt : public ::sugiyama::FacHiddenIterDirectOutput<IterVecInt, int> {
public:
  using FacHiddenIterDirectOutput::FacHiddenIterDirectOutput;
};

// These goes into implementation
template <>
class sugiyama::FacHiddenIterDirectOutput<IterVecInt, int>::Impl : public ::sugiyama::FacHiddenIterImpl<IterVecInt, std::vector<int>::iterator> {
  using FacHiddenIterImpl::FacHiddenIterImpl;
};
template class ::sugiyama::FacHiddenIterDirectOutput<IterVecInt, int>;

SCENARIO("Straightforward output iterator", "[hiter]") {

  GIVEN("An iterator for vector<int>") {
    const std::vector<int> v {5,7,9};
    THEN("It simply works") {
      auto itr = v.begin(), itrEnd = v.end();
      IterVecInt b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        REQUIRE(*b == *itr);
        REQUIRE(b != e);
      }
      REQUIRE(b == e);
    }

    THEN("The value can be modified") {
      auto itr = v.begin();
      IterVecInt b {&itr};
      *b = 29;
      REQUIRE(v[0] == 29);
    }
  }
} // end straightforward scenario

// === Indirect version: the output type need some conversion from the type inside the container ===

// These are for the header
class IterMapStr : public ::sugiyama::FacHiddenIterIndirect<IterMapStr, std::pair<const char*, const char*>> {
public:
  using FacHiddenIterIndirect::FacHiddenIterIndirect;
  void fillCache();
};

// These goes into implementation
template <>
class sugiyama::FacHiddenIterIndirect<IterMapStr, std::pair<const char*, const char*>>::Impl : public ::sugiyama::FacHiddenIterImpl<IterMapStr, std::map<std::string, std::string>::iterator> {
  using FacHiddenIterImpl::FacHiddenIterImpl;
};
template class ::sugiyama::FacHiddenIterIndirect<IterMapStr, std::pair<const char*, const char*>>;

void IterMapStr::fillCache() {
  this->m_cache = std::pair((*pimpl)->first.c_str(), (*pimpl)->second.c_str());
}

SCENARIO("Indirect iterator", "[hiter]") {

  THEN("It should be default-constructable") {
    IterMapStr empty;
  }

  GIVEN("An iterator for set<int>") {
    std::map<std::string, std::string> m {{"aa", "bb"}, {"cc", "dd"}, {"", "zzz"}};
    THEN("It simply works") {
      auto itr = m.begin(), itrEnd = m.end();
      IterMapStr b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        REQUIRE(strcmp(b->first, itr->first.c_str()) == 0);
        REQUIRE(strcmp(b->second, itr->second.c_str()) == 0);
        REQUIRE(b != e);
      }
      REQUIRE(b == e);
    }
  }
} // end straightforward scenario

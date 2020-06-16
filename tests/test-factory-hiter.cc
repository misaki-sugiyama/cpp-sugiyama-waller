#include "sugiyama/factory-hiter.h"
#include "sugiyama/factory-hiter-inl.h"
#include <catch2/catch_test_macros.hpp>

#include <set>
#include <map>
#include <string>

// === Direct version: the output type is exactly the type inside the container ===

// These are for the header
class IterSetInt : public ::sugiyama::FacHiddenIter<int, IterSetInt> {
public:
  using FacHiddenIter::FacHiddenIter;
  const value_type& operator*() const;
};

// These goes into implementation
template <>
class sugiyama::FacHiddenIter<int, IterSetInt>::Impl : public ::sugiyama::FacHiddenIterImpl<std::set<int>::iterator> {
  using FacHiddenIterImpl::FacHiddenIterImpl;
};
template class ::sugiyama::FacHiddenIter<int, IterSetInt>;

const typename IterSetInt::value_type& IterSetInt::operator*() const {
  return **pimpl;
}

SCENARIO("Straightforward iterator", "[hiter]") {

  THEN("It should be default-constructable") {
    IterSetInt empty;
  }

  GIVEN("An iterator for set<int>") {
    std::set<int> s {9,3,7};
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

// These are for the header
class IterMapStr : public ::sugiyama::FacHiddenIter<std::pair<const char*, const char*>, IterMapStr> {
public:
  using FacHiddenIter::FacHiddenIter;
  value_type&& operator*() const;
};

// These goes into implementation
template <>
class sugiyama::FacHiddenIter<std::pair<const char*, const char*>, IterMapStr>::Impl : public ::sugiyama::FacHiddenIterImpl<std::map<std::string, std::string>::iterator> {
  using FacHiddenIterImpl::FacHiddenIterImpl;
};
template class ::sugiyama::FacHiddenIter<std::pair<const char*, const char*>, IterMapStr>;

typename IterMapStr::value_type&& IterMapStr::operator*() const {
  return std::move(std::pair((*pimpl)->first.c_str(), (*pimpl)->second.c_str()));
}

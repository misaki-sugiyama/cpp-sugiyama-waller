// Hidden iterator that doesn't show the underlying iterator type
#pragma once
#include "sugiyama/factory-pimpl.h"

namespace sugiyama {

  // "Derived" isn't actually used, it's just for differentiate iterators for different containers
  template <typename T, class Derived>
  class FacHiddenIter {
  protected:
    class Impl; FacPImpl<Impl> pimpl;
  public:
    FacHiddenIter();
    FacHiddenIter(void* pItr);
    virtual ~FacHiddenIter();

    using value_type = T;
    bool operator==(const FacHiddenIter& rhs) const;
    bool operator!=(const FacHiddenIter& rhs) const;
    FacHiddenIter& operator++();
    // These two need to be defined by user if needed
    //const value_type& operator*() const;
    //const value_type* operator->() const;
  };
}


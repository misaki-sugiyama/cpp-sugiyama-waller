// Hidden iterator that doesn't show the underlying iterator type
#pragma once
#include "sugiyama/factory-pimpl.h"

namespace sugiyama {

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
    FacHiddenIter& operator--();
    value_type& operator*();
    value_type* operator->();

    void ensureCache();
    // This need to be defined by user
    // void fillCache();
  };
}


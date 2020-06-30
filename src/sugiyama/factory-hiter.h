// Hidden iterator that doesn't show the underlying iterator type
#pragma once
#include "sugiyama/factory-pimpl.h"
#include "sugiyama/factory-crtp.h"

namespace sugiyama {

  template <class Derived, typename T>
  class FacHiddenIterBase {
  protected:
    class Impl; FacPImpl<Impl> pimpl;
  public:
    FacHiddenIterBase();
    FacHiddenIterBase(void* pItr);
    virtual ~FacHiddenIterBase();

    using value_type = T;
    bool operator==(const FacHiddenIterBase& rhs) const;
    bool operator!=(const FacHiddenIterBase& rhs) const;
    FacHiddenIterBase& operator++();
    FacHiddenIterBase& operator--();
  };

  template <class Derived, typename T>
  class TraitHiddenIterDirect {
  public:
    using value_type = T;
    const value_type& operator*() const;
    //value_type& operator*();
    const value_type* operator->() const;
    //value_type* operator->();
  };

  template <class Derived, typename T>
  class FacHiddenIterDirect : public FacHiddenIterBase<Derived, T>, public TraitHiddenIterDirect<Derived, T> {
    friend class TraitHiddenIterDirect<Derived, T>;
  public:
    using FacHiddenIterBase<Derived, T>::FacHiddenIterBase;
  };

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


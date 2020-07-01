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
    FacHiddenIterBase(const void* pItr);
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
    const value_type* operator->() const;
  };

  template <class Derived, typename T>
  class FacHiddenIterDirect : public FacHiddenIterBase<Derived, T>, public TraitHiddenIterDirect<Derived, T> {
    friend class TraitHiddenIterDirect<Derived, T>;
  public:
    using FacHiddenIterBase<Derived, T>::FacHiddenIterBase;
  };

  template <class Derived, typename T>
  class TraitHiddenIterDirectOutput : public TraitHiddenIterDirect<Derived, T> {
  public:
    using value_type = T;
    value_type& operator*();
    value_type* operator->();
  };

  template <class Derived, typename T>
  class FacHiddenIterDirectOutput : public FacHiddenIterBase<Derived, T>, public TraitHiddenIterDirectOutput<Derived, T> {
    friend class TraitHiddenIterDirectOutput<Derived, T>;
  public:
    using FacHiddenIterBase<Derived, T>::FacHiddenIterBase;
  };

  template <class Derived, typename T>
  class TraitHiddenIterIndirect {
  protected:
    T m_cache;
  public:
    using value_type = T;
    void ensureCache();
    const value_type& operator*() const;
    const value_type* operator->() const;
  };

  template <class Derived, typename T>
  class FacHiddenIterIndirect : public FacHiddenIterBase<Derived, T>, public TraitHiddenIterIndirect<Derived, T> {
    friend class TraitHiddenIterIndirect<Derived, T>;
  public:
    using FacHiddenIterBase<Derived, T>::FacHiddenIterBase;
  };

}


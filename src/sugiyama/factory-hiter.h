// Hidden iterator that doesn't show the underlying iterator type
#pragma once
#include "sugiyama/pimpl.h"
#include "sugiyama/crtp.h"

namespace sugiyama {

  template <class Derived, typename T, template<class, typename> class... Caps>
  class FacHiddenIter : public Caps<Derived, T>... {
  protected:
    class Impl; PImpl<Impl> pimpl;
  public:
    FacHiddenIter();
    FacHiddenIter(const void* pItr);
    virtual ~FacHiddenIter();

    using value_type = T;
    bool operator==(const FacHiddenIter& rhs) const;
    bool operator!=(const FacHiddenIter& rhs) const;
    FacHiddenIter& operator++();
    //FacHiddenIter& operator--();
  };

  template <class Derived, typename T>
  class HiddenIterCapDirect : public CRTPHelper<HiddenIterCapDirect, Derived, T> {
  public:
    using value_type = T;
    const value_type& operator*() const;
    const value_type* operator->() const;
  };

  template <class Derived, typename T>
  using FacHiddenIterDirect = FacHiddenIter<Derived, T, HiddenIterCapDirect>;

  //template <class Derived, typename T>
  //class FacHiddenIterDirect : public FacHiddenIter<Derived, T>, public TraitHiddenIterDirect<Derived, T> {
  //  friend class TraitHiddenIterDirect<Derived, T>;
  //public:
  //  using FacHiddenIter<Derived, T>::FacHiddenIter;
  //};

  //template <class Derived, typename T>
  //class TraitHiddenIterDirectOutput : public TraitHiddenIterDirect<Derived, T> {
  //public:
  //  using value_type = T;
  //  value_type& operator*();
  //  value_type* operator->();
  //};

  //template <class Derived, typename T>
  //class FacHiddenIterDirectOutput : public FacHiddenIter<Derived, T>, public TraitHiddenIterDirectOutput<Derived, T> {
  //  friend class TraitHiddenIterDirectOutput<Derived, T>;
  //public:
  //  using FacHiddenIter<Derived, T>::FacHiddenIter;
  //};

  //template <class Derived, typename T>
  //class TraitHiddenIterIndirect : public CRTPHelper<TraitHiddenIterIndirect, Derived, T> {
  //protected:
  //  T m_cache;
  //public:
  //  using value_type = T;
  //  void ensureCache();
  //  const value_type& operator*() const;
  //  const value_type* operator->() const;
  //};

  //template <class Derived, typename T>
  //class FacHiddenIterIndirect : public FacHiddenIter<Derived, T>, public TraitHiddenIterIndirect<Derived, T> {
  //  friend class TraitHiddenIterIndirect<Derived, T>;
  //public:
  //  using FacHiddenIter<Derived, T>::FacHiddenIter;
  //};

}

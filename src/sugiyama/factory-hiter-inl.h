// The inline implementation file of the hidden iterator factory
#pragma once
#include "sugiyama/factory-pimpl-inl.h"

namespace sugiyama {

  template <typename T, typename Itr>
  class FacHiddenIterImpl {
  private:
    Itr m_it;
  public:
    T m_cache;
    bool isCacheValid {false};

    using value_type = typename Itr::value_type;
    FacHiddenIterImpl(void *pItr) : m_it{*static_cast<Itr*>(pItr)} {}
    FacHiddenIterImpl() {}
    virtual ~FacHiddenIterImpl() {}

    bool operator==(const FacHiddenIterImpl& rhs) const {
      return m_it == rhs.m_it;
    }
    FacHiddenIterImpl& operator++() {
      ++m_it;
      isCacheValid = false;
      return *this;
    }
    FacHiddenIterImpl& operator--() {
      --m_it;
      isCacheValid = false;
      return *this;
    }
    const value_type& operator*() const {
      return *m_it;
    }
    const value_type* operator->() const {
      return &(*m_it);
    }
  };

  template <typename T, class Derived>
  FacHiddenIter<T,Derived>::FacHiddenIter() : pimpl{} {}

  template <typename T, class Derived>
  FacHiddenIter<T,Derived>::FacHiddenIter(void *pItr) : pimpl{pItr} {}

  template <typename T, class Derived>
  FacHiddenIter<T,Derived>::~FacHiddenIter() {}

  template <typename T, class Derived>
  bool FacHiddenIter<T,Derived>::operator==(const FacHiddenIter& rhs) const {
    return *pimpl == *rhs.pimpl;
  }

  template <typename T, class Derived>
  bool FacHiddenIter<T,Derived>::operator!=(const FacHiddenIter& rhs) const {
    return !(this->operator==(rhs));
  }

  template <typename T, class Derived>
  FacHiddenIter<T,Derived>& FacHiddenIter<T,Derived>::operator++() {
    ++(*pimpl);
    return *this;
  }

  template <typename T, class Derived>
  FacHiddenIter<T,Derived>& FacHiddenIter<T,Derived>::operator--() {
    --(*pimpl);
    return *this;
  }

  template <typename T, class Derived>
  void FacHiddenIter<T,Derived>::ensureCache() {
    if (!pimpl->isCacheValid) {
      static_cast<Derived*>(this)->fillCache();
      pimpl->isCacheValid = true;
    }
  }

  template <typename T, class Derived>
  typename FacHiddenIter<T,Derived>::value_type& FacHiddenIter<T,Derived>::operator*() {
    ensureCache();
    return pimpl->m_cache;
  }

  template <typename T, class Derived>
  typename FacHiddenIter<T,Derived>::value_type* FacHiddenIter<T,Derived>::operator->() {
    ensureCache();
    return &(pimpl->m_cache);
  }
}

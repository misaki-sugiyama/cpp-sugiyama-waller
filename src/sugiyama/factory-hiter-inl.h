// The inline implementation file of the hidden iterator factory
#pragma once
#include "sugiyama/factory-pimpl-inl.h"

namespace sugiyama {

  template <typename Itr>
  class FacHiddenIterImpl {
  private:
    Itr m_it;
  public:
    using value_type = typename Itr::value_type;
    FacHiddenIterImpl(void *pItr) : m_it{*static_cast<Itr*>(pItr)} {}
    FacHiddenIterImpl() {}
    virtual ~FacHiddenIterImpl() {}

    bool operator==(const FacHiddenIterImpl& rhs) const {
      return m_it == rhs.m_it;
    }
    FacHiddenIterImpl& operator++() {
      ++m_it;
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
}

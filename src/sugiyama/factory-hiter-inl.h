// The inline implementation file of the hidden iterator factory
#pragma once
#include "sugiyama/factory-pimpl-inl.h"

namespace sugiyama {

  template <typename DerivedOut, typename Itr>
  class FacHiddenIterImpl {
  private:
    Itr m_it;
  public:
    bool m_isCacheValid {false};

    using value_type = typename Itr::value_type;
    FacHiddenIterImpl(const void *pItr) : m_it{*static_cast<const Itr*>(pItr)} {}
    FacHiddenIterImpl() {}
    virtual ~FacHiddenIterImpl() {}

    bool operator==(const FacHiddenIterImpl& rhs) const {
      return m_it == rhs.m_it;
    }
    FacHiddenIterImpl& operator++() {
      ++m_it;
      m_isCacheValid = false;
      return *this;
    }
    FacHiddenIterImpl& operator--() {
      --m_it;
      m_isCacheValid = false;
      return *this;
    }
    const value_type& operator*() const {
      return *m_it;
    }
    value_type& operator*() {
      return *m_it;
    }
    const value_type* operator->() const {
      return &(*m_it);
    }
    value_type* operator->() {
      return &(*m_it);
    }
  };

  template <class Derived, typename T>
  FacHiddenIterBase<Derived,T>::FacHiddenIterBase() : pimpl{} {}

  template <class Derived, typename T>
  FacHiddenIterBase<Derived,T>::FacHiddenIterBase(const void *pItr) : pimpl{pItr} {}

  template <class Derived, typename T>
  FacHiddenIterBase<Derived,T>::~FacHiddenIterBase() {}

  template <class Derived, typename T>
  bool FacHiddenIterBase<Derived,T>::operator==(const FacHiddenIterBase& rhs) const {
    return *pimpl == *rhs.pimpl;
  }

  template <class Derived, typename T>
  bool FacHiddenIterBase<Derived,T>::operator!=(const FacHiddenIterBase& rhs) const {
    return !(this->operator==(rhs));
  }

  template <class Derived, typename T>
  FacHiddenIterBase<Derived,T>& FacHiddenIterBase<Derived,T>::operator++() {
    ++(*pimpl);
    return *this;
  }

  template <class Derived, typename T>
  FacHiddenIterBase<Derived,T>& FacHiddenIterBase<Derived,T>::operator--() {
    --(*pimpl);
    return *this;
  }

  template <class Derived, typename T>
  const typename TraitHiddenIterDirect<Derived,T>::value_type& TraitHiddenIterDirect<Derived,T>::operator*() const {
    return *(*(static_cast<const Derived*>(this)->pimpl));
  }

  template <class Derived, typename T>
  const typename TraitHiddenIterDirect<Derived,T>::value_type* TraitHiddenIterDirect<Derived,T>::operator->() const {
    return &*(*(static_cast<const Derived*>(this)->pimpl));
  }

  template <class Derived, typename T>
  typename TraitHiddenIterDirectOutput<Derived,T>::value_type& TraitHiddenIterDirectOutput<Derived,T>::operator*() {
    return *(*(static_cast<Derived*>(this)->pimpl));
  }

  template <class Derived, typename T>
  typename TraitHiddenIterDirectOutput<Derived,T>::value_type* TraitHiddenIterDirectOutput<Derived,T>::operator->() {
    return &*(*(static_cast<Derived*>(this)->pimpl));
  }

  template <class Derived, typename T>
  void TraitHiddenIterIndirect<Derived,T>::ensureCache() {
    if (!static_cast<Derived*>(this)->pimpl->m_isCacheValid) {
      static_cast<Derived*>(this)->fillCache();
      static_cast<Derived*>(this)->pimpl->m_isCacheValid = true;
    }
  }

  template <class Derived, typename T>
  const typename TraitHiddenIterIndirect<Derived,T>::value_type& TraitHiddenIterIndirect<Derived,T>::operator*() const {
    const_cast<TraitHiddenIterIndirect<Derived,T>*>(this)->ensureCache();
    return m_cache;
  }

  template <class Derived, typename T>
  const typename TraitHiddenIterIndirect<Derived,T>::value_type* TraitHiddenIterIndirect<Derived,T>::operator->() const {
    const_cast<TraitHiddenIterIndirect<Derived,T>*>(this)->ensureCache();
    return &(m_cache);
  }
}

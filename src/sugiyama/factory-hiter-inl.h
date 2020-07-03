// The inline implementation file of the hidden iterator factory
#pragma once
#include "sugiyama/pimpl-inl.h"

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

  template <class Derived, typename T, template<class, typename> class... Caps>
  FacHiddenIter<Derived,T,Caps...>::FacHiddenIter() : pimpl{} {}

  template <class Derived, typename T>
  FacHiddenIter<Derived,T>::FacHiddenIter(const void *pItr) : pimpl{pItr} {}

  template <class Derived, typename T>
  FacHiddenIter<Derived,T>::~FacHiddenIter() {}

  template <class Derived, typename T>
  bool FacHiddenIter<Derived,T>::operator==(const FacHiddenIter& rhs) const {
    return *pimpl == *rhs.pimpl;
  }

  template <class Derived, typename T>
  bool FacHiddenIter<Derived,T>::operator!=(const FacHiddenIter& rhs) const {
    return !(this->operator==(rhs));
  }

  template <class Derived, typename T>
  FacHiddenIter<Derived,T>& FacHiddenIter<Derived,T>::operator++() {
    ++(*pimpl);
    return *this;
  }

  //template <class Derived, typename T>
  //FacHiddenIter<Derived,T>& FacHiddenIter<Derived,T>::operator--() {
  //  --(*pimpl);
  //  return *this;
  //}

  template <class Derived, typename T>
  const typename HiddenIterCapDirect<Derived,T>::value_type& HiddenIterCapDirect<Derived,T>::operator*() const {
    return **this->derived().pimpl;
  }

  template <class Derived, typename T>
  const typename HiddenIterCapDirect<Derived,T>::value_type* HiddenIterCapDirect<Derived,T>::operator->() const {
    return &**this->derived().pimpl;
  }

  //template <class Derived, typename T>
  //typename HiddenIterCapDirectOutput<Derived,T>::value_type& HiddenIterCapDirectOutput<Derived,T>::operator*() {
  //  return **this->derived().pimpl;
  //}

  //template <class Derived, typename T>
  //typename HiddenIterCapDirectOutput<Derived,T>::value_type* HiddenIterCapDirectOutput<Derived,T>::operator->() {
  //  return &**this->derived().pimpl;
  //}

  //template <class Derived, typename T>
  //void TraitHiddenIterIndirect<Derived,T>::ensureCache() {
  //  if (!this->derived().pimpl->m_isCacheValid) {
  //    this->derived().fillCache();
  //    this->derived().pimpl->m_isCacheValid = true;
  //  }
  //}

  //template <class Derived, typename T>
  //const typename TraitHiddenIterIndirect<Derived,T>::value_type& TraitHiddenIterIndirect<Derived,T>::operator*() const {
  //  const_cast<TraitHiddenIterIndirect<Derived,T>*>(this)->ensureCache();
  //  return m_cache;
  //}

  //template <class Derived, typename T>
  //const typename TraitHiddenIterIndirect<Derived,T>::value_type* TraitHiddenIterIndirect<Derived,T>::operator->() const {
  //  const_cast<TraitHiddenIterIndirect<Derived,T>*>(this)->ensureCache();
  //  return &(m_cache);
  //}
}

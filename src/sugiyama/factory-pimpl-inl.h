// The inline implementation file of the pimpl factory
#pragma once
#include "sugiyama/factory-pimpl.h"

#include <utility> // for forward

namespace sugiyama {

  template <class T>
  template <typename... Args>
  FacPImpl<T>::FacPImpl(Args&&... args) : m_ptr{new T{std::forward<Args>(args)...}} {}

  template <class T>
  FacPImpl<T>::~FacPImpl() {
    if (m_ptr) delete m_ptr;
  }

  // == Move and Copy ==

  template <class T>
  FacPImpl<T>::FacPImpl(FacPImpl<T>&& rhs) noexcept : m_ptr{rhs.m_ptr} {
    rhs.m_ptr = nullptr;
  }

  template <class T>
  FacPImpl<T>& FacPImpl<T>::operator=(FacPImpl<T>&& rhs) noexcept {
    if (m_ptr != rhs.m_ptr) {
      if (m_ptr) delete m_ptr;
      m_ptr = rhs.m_ptr;
      rhs.m_ptr = nullptr;
    }

    return *this;
  }

  template <class T>
  FacPImpl<T>::FacPImpl(const FacPImpl<T>& rhs) : m_ptr{new T{*rhs.m_ptr}} {}

  template <class T>
  FacPImpl<T>& FacPImpl<T>::operator=(const FacPImpl<T>& rhs) {
    if (m_ptr != rhs.m_ptr) {
      if (m_ptr) delete m_ptr;
      m_ptr = new T{*rhs.m_ptr};
    }
    return *this;
  }

  // == Overloadings ==

  template <class T>
  T* FacPImpl<T>::operator->() { return m_ptr; }

  template <class T>
  const T* FacPImpl<T>::operator->() const { return m_ptr; }

  template <class T>
  T& FacPImpl<T>::operator*() { return *m_ptr; }

  template <class T>
  const T& FacPImpl<T>::operator*() const { return *m_ptr; }

}

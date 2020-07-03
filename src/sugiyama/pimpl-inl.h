// The inline implementation file of the pimpl factory
#pragma once
#include "sugiyama/pimpl.h"

#include <utility> // for forward

namespace sugiyama {

  template <class T>
  template <typename... Args>
  PImpl<T>::PImpl(Args&&... args) : m_ptr{new T{std::forward<Args>(args)...}} {}

  template <class T>
  PImpl<T>::~PImpl() {
    if (m_ptr) delete m_ptr;
  }

  // == Move and Copy ==

  template <class T>
  PImpl<T>::PImpl(PImpl<T>&& rhs) noexcept : m_ptr{rhs.m_ptr} {
    rhs.m_ptr = nullptr;
  }

  template <class T>
  PImpl<T>& PImpl<T>::operator=(PImpl<T>&& rhs) noexcept {
    if (m_ptr != rhs.m_ptr) {
      if (m_ptr) delete m_ptr;
      m_ptr = rhs.m_ptr;
      rhs.m_ptr = nullptr;
    }

    return *this;
  }

  template <class T>
  PImpl<T>::PImpl(const PImpl<T>& rhs) : m_ptr{new T{*rhs.m_ptr}} {}

  template <class T>
  PImpl<T>& PImpl<T>::operator=(const PImpl<T>& rhs) {
    if (m_ptr != rhs.m_ptr) {
      if (m_ptr) delete m_ptr;
      m_ptr = new T{*rhs.m_ptr};
    }
    return *this;
  }

  // == Overloadings ==

  template <class T>
  T* PImpl<T>::operator->() { return m_ptr; }

  template <class T>
  const T* PImpl<T>::operator->() const { return m_ptr; }

  template <class T>
  T& PImpl<T>::operator*() { return *m_ptr; }

  template <class T>
  const T& PImpl<T>::operator*() const { return *m_ptr; }

}

// == Convenient macros ==

#define SUGIYAMA_PIMPL_INST(ClassImpl) \
  template class ::sugiyama::PImpl<ClassImpl>;

#define SUGIYAMA_PIMPL_CPMV_DEF(ClassNameWithNamespace, ClassName) \
  ClassNameWithNamespace::~ClassName() = default; \
  ClassNameWithNamespace::ClassName(ClassNameWithNamespace&& rhs) noexcept = default; \
  ClassNameWithNamespace& ClassNameWithNamespace::operator=(ClassNameWithNamespace&& rhs) noexcept = default; \
  ClassNameWithNamespace::ClassName(const ClassNameWithNamespace& rhs) = default; \
  ClassNameWithNamespace& ClassNameWithNamespace::operator=(const ClassNameWithNamespace& rhs) = default;

// The factory to produce pimpl classes
#pragma once

namespace sugiyama {

  template <class T>
  class FacPImpl {
  private:
    // Yes, horrible raw pointer in order not to include smart pointer headers here
    T* m_ptr {nullptr};
  public:
    // Ctor Dtor etc.
    template <typename... Args> FacPImpl(Args&& ...);
    ~FacPImpl();

    // Move and Copy
    FacPImpl(FacPImpl<T>&& rhs) noexcept;
    FacPImpl<T>& operator=(FacPImpl<T>&& rhs) noexcept;
    FacPImpl(const FacPImpl<T>& rhs);
    FacPImpl<T>& operator=(const FacPImpl<T>& rhs);

    // Overloadings to get the actual underlying implementation object
    T* operator->();
    const T* operator->() const;
    T& operator*();
    const T& operator*() const;
  };

}

// == Convenient macros ==

#define SUGIYAMA_PIMPL_CPMV_DEC(ClassName) \
  ~ClassName(); \
  ClassName(ClassName&& rhs) noexcept; \
  ClassName& operator=(ClassName&& rhs) noexcept; \
  ClassName(const ClassName& rhs); \
  ClassName& operator=(const ClassName& rhs);

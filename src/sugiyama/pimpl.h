// The factory to produce pimpl classes
#pragma once

namespace sugiyama {

  template <class T>
  class PImpl {
  private:
    // Yes, horrible raw pointer in order not to include smart pointer headers here
    T* m_ptr {nullptr};
  public:
    // Ctor Dtor etc.
    template <typename... Args> PImpl(Args&& ...);
    ~PImpl();

    // Move and Copy
    PImpl(PImpl<T>&& rhs) noexcept;
    PImpl<T>& operator=(PImpl<T>&& rhs) noexcept;
    PImpl(const PImpl<T>& rhs);
    PImpl<T>& operator=(const PImpl<T>& rhs);

    // Overloadings to get the actual underlying implementation object
    T* operator->();
    const T* operator->() const;
    T& operator*();
    const T& operator*() const;
  };

}

// == Convenient macros ==

#define SUGIYAMA_PIMPL_FIVE_DEC(ClassName) \
  virtual ~ClassName(); \
  ClassName(ClassName&& rhs) noexcept; \
  virtual ClassName& operator=(ClassName&& rhs) noexcept; \
  ClassName(const ClassName& rhs); \
  virtual ClassName& operator=(const ClassName& rhs);

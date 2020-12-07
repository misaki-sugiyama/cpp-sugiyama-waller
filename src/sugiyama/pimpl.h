// The factory to produce pimpl classes
#pragma once

namespace sugiyama {

  template <class T>
  class PImpl {
  private:
    // Yes, horrible raw pointer in order not to include smart pointer headers here
    T* m_ptr {nullptr};
  public:
    // Ctor Dtor move copy etc.
    template <typename... Args> PImpl(Args&& ...);
    ~PImpl();
    PImpl(PImpl&& rhs) noexcept;
    PImpl& operator=(PImpl&& rhs) noexcept;
    PImpl(const PImpl& rhs);
    PImpl& operator=(const PImpl& rhs);

    // Overloadings to get the actual underlying implementation object
    T* operator->();
    const T* operator->() const;
    T& operator*();
    const T& operator*() const;
  };

}

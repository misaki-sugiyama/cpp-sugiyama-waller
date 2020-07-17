// The factory to produce pimpl classes
#pragma once
#include "sugiyama/ro5.h"

namespace sugiyama {

  template <class T>
  class PImpl {
  private:
    // Yes, horrible raw pointer in order not to include smart pointer headers here
    T* m_ptr {nullptr};
  public:
    // Ctor Dtor move copy etc.
    template <typename... Args> PImpl(Args&& ...);
    SUGIYAMA_RO5_DEC(PImpl);

    // Overloadings to get the actual underlying implementation object
    T* operator->();
    const T* operator->() const;
    T& operator*();
    const T& operator*() const;
  };

}

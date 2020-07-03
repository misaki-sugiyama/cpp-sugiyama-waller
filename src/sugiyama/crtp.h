// A helper class to reduce CRTP boilerplate (static_cast)
#pragma once

namespace sugiyama {

  template <template<typename, typename...> class TypeCRTP, class Derived, typename... Ts>
  class CRTPHelper {
  private:
    // Put everything in private for safe-guarding
    Derived& derived() {
      return static_cast<Derived&>(*this);
    }
    const Derived& derived() const {
      return static_cast<const Derived&>(*this);
    }
    friend TypeCRTP<Derived, Ts...>;
  };

}

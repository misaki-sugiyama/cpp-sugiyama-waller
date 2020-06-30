// The factory to slightly reduce CRTP boilerplate
#pragma once

namespace sugiyama {

  template <class Derived, template<typename, typename...> class TypeCRTP, typename... Ts>
  class FacCRTP {
  protected:
    Derived& derived() {
      return static_cast<Derived&>(*this);
    }
    const Derived& derived() const {
      return static_cast<const Derived&>(*this);
    }
  private:
    // Safeguards
    FacCRTP() {}
    friend TypeCRTP<Derived, Ts...>;
  };

}

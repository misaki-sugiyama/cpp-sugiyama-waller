// Hidden iterator that doesn't show the underlying iterator type
#pragma once
#include "sugiyama/iterator-registry.h"
#include "sugiyama/pimpl.h"
#include "sugiyama/uniq.h"
#include "sugiyama/itf-registrable.h"

#include "CorradePointer.h"
using Corrade::Containers::Pointer;

#include <utility> // for forward
#include <type_traits> // for type check etc.
#include <cstddef> // for size_t

namespace sugiyama {

  // Empty base class for checking class hierarchy
  class IRegistry {};

  // Factory to generate a registry given interface and constructor argument types
  template <class Derived, class Itf, typename... Args>
  class FacRegistry : public IRegistry {
    static_assert(std::is_base_of<IRegistrable, Itf>::value, "Itf must be derived from IRegistrable");
  protected:
    class Impl; PImpl<Impl> pimpl;

  public:
    using TypeCreator = Pointer<Itf>(*)(Args...);

    // The singleton utility
    static Derived& obj();

    // Main interface
    bool addEntry(const char* name, const char* desc, const TypeCreator& creator);
    Pointer<Itf> make(const char* name, Args... args) const;

    // Inspection utilities
    bool has(const char* name) const;
    const char* getDesc(const char* name) const;
    size_t size() const;
    IterRegistry begin() const;
    IterRegistry end() const;

    // Header-only utilities
    // These need to be defined in the main header, since we cannot pre-instantiate all possible Ts
    template <class T>
    TypeCreator getCreator() const {
      return [](Args... args) -> Pointer<Itf> {
        return Corrade::Containers::pointer<T>(std::forward<Args>(args)...);
      };
    }

    template <class T>
    bool reg() {
      return addEntry(T::name, T::desc, getCreator<T>());
    }
  };

  // A small helper factory to associate registry to class
  template <class Reg>
  class FacRegistryAssociator {
    static_assert(std::is_base_of<IRegistry, Reg>::value, "Reg must be derived from FacRegistry");
  public:
    using Registry = Reg;
  };

}

#define SUGIYAMA_REG(ClassName) \
  namespace { \
    static bool __UNIQLOCALNAME__ = ClassName::Registry::obj().reg<ClassName>(); \
  }

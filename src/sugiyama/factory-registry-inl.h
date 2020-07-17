// The inline implementation file of the hidden iterator factory
#pragma once
#include "sugiyama/factory-registry.h"
#include "sugiyama/crtp.h"
#include "sugiyama/pimpl-inl.h"
#include "sugiyama/exception-registry.h"

#include <map>
#include <string>

namespace sugiyama {

  template <class Derived, class Itf, typename... Args>
  using TypeCreator = typename FacRegistry<Derived, Itf, Args...>::TypeCreator;

  template <class Derived, class Itf, typename... Args>
  using TypeCreatorMap = std::map<std::string, TypeCreator<Derived, Itf, Args...>, std::less<>>;

  using TypeDescMap = std::map<std::string, std::string, std::less<>>;

  template <class Derived, class Itf, typename... Args>
  class FacRegistry<Derived, Itf, Args...>::Impl {
  public:
    TypeCreatorMap<Derived, Itf, Args...> mCreator;
    TypeDescMap mDesc;
  };

  template <class Derived, class Itf, typename... Args>
  Derived& FacRegistry<Derived, Itf, Args...>::obj() {
    static Derived o;
    return o;
  }

  // Main interfaces

  template <class Derived, class Itf, typename... Args>
  bool FacRegistry<Derived, Itf, Args...>::addEntry(const char* name, const char* desc, const TypeCreator& creator) {
    if (creator == nullptr) {
      throw ExceptionRegistryAddNull(name);
    }

    if (!has(name)) {
      pimpl->mDesc.emplace(name, desc);
      pimpl->mCreator.emplace(name, creator);
    } else {
      throw ExceptionRegistryAddDup(name);
    }

    // Just return something to keep the global variable alive
    return true;
  }

  template <class Derived, class Itf, typename... Args>
  Pointer<Itf> FacRegistry<Derived, Itf, Args...>::make(const char* name, Args... args) const {
    if (has(name)) {
      auto creator = pimpl->mCreator.find(name)->second;
      return creator(std::forward<Args>(args)...);
    } else {
      throw ExceptionRegistryOutOfRange(name);
    }
  }

  // Inspection utils
  template <class Derived, class Itf, typename... Args>
  bool FacRegistry<Derived, Itf, Args...>::has(const char* name) const {
    return pimpl->mDesc.count(name) > 0;
  }

  template <class Derived, class Itf, typename... Args>
  const char* FacRegistry<Derived, Itf, Args...>::getDesc(const char* name) const {
    if (has(name)) {
      return pimpl->mDesc.find(name)->second.c_str();
    } else {
      throw ExceptionRegistryOutOfRange(name);
    }
  }

  template <class Derived, class Itf, typename... Args>
  size_t FacRegistry<Derived, Itf, Args...>::size() const {
    return pimpl->mDesc.size();
  }

  template <class Derived, class Itf, typename... Args>
  IterRegistry FacRegistry<Derived, Itf, Args...>::begin() const {
    auto itr = pimpl->mDesc.begin();
    return IterRegistry{&itr};
  }

  template <class Derived, class Itf, typename... Args>
  IterRegistry FacRegistry<Derived, Itf, Args...>::end() const {
    auto itr = pimpl->mDesc.end();
    return IterRegistry{&itr};
  }

}

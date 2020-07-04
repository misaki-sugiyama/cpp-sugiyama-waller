// The inline implementation file of the hidden iterator factory
#pragma once
#include "sugiyama/crtp.h"
#include "sugiyama/pimpl-inl.h"

namespace sugiyama {

  template <typename DerivedOut, typename Itr>
  class FacHiddenIterImpl {
  private:
    Itr m_it;
  public:
    bool m_isCacheValid {false};

    using value_type = typename Itr::value_type;
    FacHiddenIterImpl(const void *pItr) : m_it{*static_cast<const Itr*>(pItr)} {}
    FacHiddenIterImpl() {}
    virtual ~FacHiddenIterImpl() {}

    bool operator==(const FacHiddenIterImpl& rhs) const {
      return m_it == rhs.m_it;
    }
    FacHiddenIterImpl& operator++() {
      ++m_it;
      m_isCacheValid = false;
      return *this;
    }
    FacHiddenIterImpl& operator--() {
      --m_it;
      m_isCacheValid = false;
      return *this;
    }
    const value_type& operator*() const {
      return *m_it;
    }
    value_type& operator*() {
      return *m_it;
    }
    const value_type* operator->() const {
      return &(*m_it);
    }
    value_type* operator->() {
      return &(*m_it);
    }
  };

  template <class Derived, typename T, template<class, typename> class... Caps>
  FacHiddenIter<Derived,T,Caps...>::FacHiddenIter() : pimpl{} {}

  template <class Derived, typename T, template<class, typename> class... Caps>
  FacHiddenIter<Derived,T,Caps...>::FacHiddenIter(const void *pItr) : pimpl{pItr} {}

  template <class Derived, typename T, template<class, typename> class... Caps>
  FacHiddenIter<Derived,T,Caps...>::~FacHiddenIter() {}

  template <class Derived, typename T, template<class, typename> class... Caps>
  bool FacHiddenIter<Derived,T,Caps...>::operator==(const FacHiddenIter& rhs) const {
    return *pimpl == *rhs.pimpl;
  }

  template <class Derived, typename T, template<class, typename> class... Caps>
  bool FacHiddenIter<Derived,T,Caps...>::operator!=(const FacHiddenIter& rhs) const {
    return !(this->operator==(rhs));
  }

  template <class Derived, typename T, template<class, typename> class... Caps>
  FacHiddenIter<Derived,T,Caps...>& FacHiddenIter<Derived,T,Caps...>::operator++() {
    ++(*pimpl);
    return *this;
  }

  template <class Derived, typename T>
  const typename HiddenIterCap::Input<Derived,T>::value_type& HiddenIterCap::Input<Derived,T>::operator*() const {
    return **DERIVEDC.pimpl;
  }

  template <class Derived, typename T>
  const typename HiddenIterCap::Input<Derived,T>::value_type* HiddenIterCap::Input<Derived,T>::operator->() const {
    return &**DERIVEDC.pimpl;
  }

  template <class Derived, typename T>
  typename HiddenIterCap::Output<Derived,T>::value_type& HiddenIterCap::Output<Derived,T>::operator*() {
    return **DERIVED.pimpl;
  }

  template <class Derived, typename T>
  typename HiddenIterCap::Output<Derived,T>::value_type* HiddenIterCap::Output<Derived,T>::operator->() {
    return &**DERIVED.pimpl;
  }

  template <class Derived, typename T>
  HiddenIterCap::Bidir<Derived,T>& HiddenIterCap::Bidir<Derived,T>::operator--() {
    --(*DERIVED.pimpl);
    return *this;
  }

  //template <class Derived, typename T>
  //void TraitHiddenIterIndirect<Derived,T>::ensureCache() {
  //  if (!DERIVED.pimpl->m_isCacheValid) {
  //    DERIVED.fillCache();
  //    DERIVED.pimpl->m_isCacheValid = true;
  //  }
  //}

  //template <class Derived, typename T>
  //const typename TraitHiddenIterIndirect<Derived,T>::value_type& TraitHiddenIterIndirect<Derived,T>::operator*() const {
  //  const_cast<TraitHiddenIterIndirect<Derived,T>*>(this)->ensureCache();
  //  return m_cache;
  //}

  //template <class Derived, typename T>
  //const typename TraitHiddenIterIndirect<Derived,T>::value_type* TraitHiddenIterIndirect<Derived,T>::operator->() const {
  //  const_cast<TraitHiddenIterIndirect<Derived,T>*>(this)->ensureCache();
  //  return &(m_cache);
  //}
}

#define SUGIYAMA_HITER_INST_IMPL(IterClass, Derived, T, T2) \
  template <> \
  class IterClass<Derived, T>::Impl : \
      public ::sugiyama::FacHiddenIterImpl<Derived, T2> { \
    using FacHiddenIterImpl::FacHiddenIterImpl; \
  };

#define SUGIYAMA_HITER_INST_INPUT(Derived, T, T2) \
  SUGIYAMA_HITER_INST_IMPL(sugiyama::FacHiddenIterInput, Derived, T, T2); \
  template class ::sugiyama::FacHiddenIter<Derived, T, ::sugiyama::HiddenIterCap::Input>; \
  template class ::sugiyama::HiddenIterCap::Input<Derived, T>;

#define SUGIYAMA_HITER_INST_OUTPUT(Derived, T, T2) \
  SUGIYAMA_HITER_INST_IMPL(sugiyama::FacHiddenIterOutput, Derived, T, T2); \
  template class ::sugiyama::FacHiddenIter<Derived, T, ::sugiyama::HiddenIterCap::Output>; \
  template class ::sugiyama::HiddenIterCap::Output<Derived, T>;

#define SUGIYAMA_HITER_INST_BIINPUT(Derived, T, T2) \
  SUGIYAMA_HITER_INST_IMPL(sugiyama::FacHiddenIterBiOutput, Derived, T, T2); \
  template class ::sugiyama::FacHiddenIter<Derived, T, ::sugiyama::HiddenIterCap::Bidir, ::sugiyama::HiddenIterCap::Output>; \
  template class ::sugiyama::HiddenIterCap::Bidir<Derived, T>; \
  template class ::sugiyama::HiddenIterCap::Output<Derived, T>;

#define SUGIYAMA_HITER_INST_BIOUTPUT(Derived, T, T2) \
  SUGIYAMA_HITER_INST_IMPL(sugiyama::FacHiddenIterBiOutput, Derived, T, T2); \
  template class ::sugiyama::FacHiddenIter<Derived, T, ::sugiyama::HiddenIterCap::Bidir, ::sugiyama::HiddenIterCap::Output>; \
  template class ::sugiyama::HiddenIterCap::Bidir<Derived, T>; \
  template class ::sugiyama::HiddenIterCap::Output<Derived, T>;

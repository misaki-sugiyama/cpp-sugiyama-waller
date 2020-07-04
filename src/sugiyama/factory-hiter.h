// Hidden iterator that doesn't show the underlying iterator type
#pragma once
#include "sugiyama/pimpl.h"

namespace sugiyama {

  namespace HiddenIterCap {

    template <class Derived, typename T>
    class Input {
    public:
      using value_type = T;
      const value_type& operator*() const;
      const value_type* operator->() const;
    };

    template <class Derived, typename T>
    class Output : public Input<Derived, T> {
    public:
      using value_type = T;
      value_type& operator*();
      value_type* operator->();
    };

    template <class Derived, typename T>
    class Bidir {
    public:
      Bidir& operator--();
    };

  }

  template <class Derived, typename T, template<class, typename> class... Caps>
  class FacHiddenIter : public Caps<Derived, T>... {
    // Just friend every possible Cap classes here
    friend class HiddenIterCap::Input<Derived, T>;
    friend class HiddenIterCap::Output<Derived, T>;
    friend class HiddenIterCap::Bidir<Derived, T>;
  protected:
    class Impl; PImpl<Impl> pimpl;
  public:
    FacHiddenIter();
    FacHiddenIter(const void* pItr);
    virtual ~FacHiddenIter();

    using value_type = T;
    bool operator==(const FacHiddenIter& rhs) const;
    bool operator!=(const FacHiddenIter& rhs) const;
    FacHiddenIter& operator++();
  };

  template <class Derived, typename T>
  using FacHiddenIterInput = FacHiddenIter<Derived, T, HiddenIterCap::Input>;

  template <class Derived, typename T>
  using FacHiddenIterOutput = FacHiddenIter<Derived, T, HiddenIterCap::Output>;

  template <class Derived, typename T>
  using FacHiddenIterBiInput = FacHiddenIter<Derived, T, HiddenIterCap::Bidir, HiddenIterCap::Input>;

  template <class Derived, typename T>
  using FacHiddenIterBiOutput = FacHiddenIter<Derived, T, HiddenIterCap::Bidir, HiddenIterCap::Output>;


  //template <class Derived, typename T>
  //class TraitHiddenIterIndirect : public CRTPHelper<TraitHiddenIterIndirect, Derived, T> {
  //protected:
  //  T m_cache;
  //public:
  //  using value_type = T;
  //  void ensureCache();
  //  const value_type& operator*() const;
  //  const value_type* operator->() const;
  //};

  //template <class Derived, typename T>
  //class FacHiddenIterIndirect : public FacHiddenIter<Derived, T>, public TraitHiddenIterIndirect<Derived, T> {
  //  friend class TraitHiddenIterIndirect<Derived, T>;
  //public:
  //  using FacHiddenIter<Derived, T>::FacHiddenIter;
  //};

}

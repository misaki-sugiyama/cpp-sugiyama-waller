#include "hiter-direct.sub.h"
#include "sugiyama/factory-hiter-inl.h"

#include <forward_list>

template <>
class sugiyama::FacHiddenIter<IterSListInt, int>::Impl : public ::sugiyama::FacHiddenIterImpl<IterSListInt, std::forward_list<int>::iterator> {
  using FacHiddenIterImpl::FacHiddenIterImpl;
};
template class ::sugiyama::FacHiddenIterDirect<IterSListInt, int>;
template class ::sugiyama::FacHiddenIter<IterSListInt, int>;
template class ::sugiyama::TraitHiddenIterDirect<IterSListInt, int>;

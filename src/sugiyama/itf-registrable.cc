// The interface of registrable class: some base implementation things
#include "sugiyama/itf-registrable.h"
#include "sugiyama/ro5.h"

namespace sugiyama {
  SUGIYAMA_RO5_DEF(IRegistrable, IRegistrable);
  IRegistrable::IRegistrable() = default;
}

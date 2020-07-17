// exceptions during registry usage
#pragma once
#include "sugiyama/exception.h"

namespace sugiyama {

  class ExceptionRegistryAddNull : public exception {
  public:
    using exception::exception;
  };
  class ExceptionRegistryAddDup : public exception {
  public:
    using exception::exception;
  };
  class ExceptionRegistryOutOfRange : public exception {
  public:
    using exception::exception;
  };

}

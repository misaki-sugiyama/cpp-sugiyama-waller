// Base exception
#pragma once

#include <exception>

// The default size limit of exception string
#ifndef SZEXCEPTION
  #define SZEXCEPTION 1024
#endif

namespace sugiyama {

  // This exception base class is for in general all waller-derived libraries
  class exception : public std::exception {
    static_assert(SZEXCEPTION > 32);
  private:
    char m_what[SZEXCEPTION]; // Yep, that's the size limit
  public:
    explicit exception();
    explicit exception(const char* what);
    explicit exception(int what);
    explicit exception(long what);
    explicit exception(float what);
    explicit exception(double what);
    virtual const char* what() const noexcept;
  };

}

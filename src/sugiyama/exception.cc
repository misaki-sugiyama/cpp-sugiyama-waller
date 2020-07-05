#include "sugiyama/exception.h"

#include <cstring>
#include <cstdio>

namespace sugiyama {

  exception::exception() {
    m_what[0] = '\0';
  }
  exception::exception(const char* what) {
    strncpy(m_what, what, SZEXCEPTION);
    m_what[SZEXCEPTION-1] = '\0';
  }
  exception::exception(int what) {
    snprintf(m_what, SZEXCEPTION, "%d", what);
  }
  exception::exception(long what) {
    snprintf(m_what, SZEXCEPTION, "%ld", what);
  }
  exception::exception(float what) {
    snprintf(m_what, SZEXCEPTION, "%lf", what);
  }
  exception::exception(double what) {
    snprintf(m_what, SZEXCEPTION, "%lf", what);
  }
  const char* exception::what() const noexcept {
    return m_what;
  }

}

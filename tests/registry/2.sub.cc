#include "2.sub.class.h"

class Subject2a : public Subject2 {
public:
  SUGIYAMA_NAME_DESC("Subject2a", "Description2a");
  using Subject2::Subject2;
  virtual int get() {return a+b;}
};
SUGIYAMA_REG(Subject2a);

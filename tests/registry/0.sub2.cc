#include "0.sub.class.h"

class Subject0b : public Subject0 {
public:
  SUGIYAMA_NAME_DESC("Subject0b", "Description0b");
  using Subject0::Subject0;
  virtual int get() {return 2;}
};
SUGIYAMA_REG(Subject0b);

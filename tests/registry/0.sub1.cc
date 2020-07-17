#include "sub0.class.h"

class Subject0a : public Subject0 {
public:
  SUGIYAMA_NAME_DESC("Subject0a", "Description0a");
  virtual int get() {return 1;}
};
SUGIYAMA_REG(Subject0a);

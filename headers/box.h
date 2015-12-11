#ifndef __BOX
#define __BOX

#include "pos.h"

class Box{
public:
  Pos pos;
  bool compare(Box box2);
};


#endif
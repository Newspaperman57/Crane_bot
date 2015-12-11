#ifndef __BOX
#define __BOX

#include "pos.h"

class Box{
public:
  Pos pos;
  int color;
  bool compare(Box box2);
  Box(int, int, int);
};


#endif
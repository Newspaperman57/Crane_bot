#ifndef __BOX
#define __BOX

#include "pos.h"

typedef struct _box{
  Pos pos;
} Box;

bool compare(Box box1, Box box2);

#endif
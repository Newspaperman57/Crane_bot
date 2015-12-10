#include "box.h"

bool compare(Box box1, Box box2) {
  if(box1.pos.y == box2.pos.y && box1.pos.x == box2.pos.x)
    return true;
  else
    return false;
}
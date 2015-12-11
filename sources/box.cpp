#include "box.h"

bool Box::compare(Box box2) {
  if(pos.y == box2.pos.y && pos.x == box2.pos.x)
    return true;
  else
    return false;
}
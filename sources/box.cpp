#include "box.h"

Box::Box(int n_x, int n_y, int n_color) {
  pos.x = n_x;
  pos.y = n_y;
  color = n_color;
}

bool Box::compare(Box box2) {
  if(pos.y == box2.pos.y && pos.x == box2.pos.x && color == box2.color)
    return true;
  else
    return false;
}
#include "crane.h"

void Crane::Init() {
  printf("INIT CRANE\n");
  pos = (Pos){0,0};
  closedGrab = false;
  grabbed = -1;
}

int Crane::GoLeft() {
  pos.y--;
  return 1;
}

int Crane::GoRight() {
  pos.y++;
  return 1;
}

int Crane::Grab(std::vector<Box> *box, int height) {
  if(closedGrab) { // Drop something
    (*box)[grabbed].pos.y = pos.y;
    // Find highest box and place grabbed box on top. If highest box is at (1, x), DIE MOTHERFUCKER 
    int highestBox = height-1;
    int i = 0;
    while((int)(*box).size() > i) {
      if((*box)[i].pos.y == pos.y && i != grabbed)
        if((*box)[i].pos.x < highestBox)
          highestBox = (*box)[i].pos.x;
      i++;
    }
    if(highestBox == 0) {
      printf("No room for box!");
    }
    (*box)[grabbed].pos.x = highestBox-1;
    closedGrab = false;
  } else { // Pick something up
    // Find box right underneath crane
    int highestBox = height;
    int i = 0;
    while((int)(*box).size() > i) {
      if((*box)[i].pos.y == pos.y)
        if((*box)[i].pos.x < (*box)[highestBox].pos.x)
          highestBox = i;
      i++;
    }
    // If not box is present, don't set ClosedGrab
    if(highestBox != height) {
      // Move box to (0, height) to indicate that it's in the crane
      (*box)[highestBox].pos.x = 0;
      (*box)[highestBox].pos.y = 0;

      // grabbed = box's entry
      grabbed = highestBox;
      closedGrab = true;
    }
  }
  return 1;
}
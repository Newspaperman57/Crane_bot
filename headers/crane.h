#ifndef __CRANE
#define __CRANE

#include <vector>
#include <cstdio>

#include "pos.h"
#include "box.h"

class Crane {
private:
public:
  Pos pos;
  bool closedGrab;
  int grabbed;
  void Init();
  int GoLeft();
  int GoRight();
  int Grab(std::vector<Box> *box, int height);
};

#endif
#ifndef __SCENE
#define __SCENE

#include <vector>

#include "box.h"
#include "crane.h"

enum {
  SUCCES,
  FAILURE,
  NOT_DONE
};

enum FUNC{
  FUNC1,
  FUNC2,
  FUNC3,
  FUNC4,
  FUNC5,
  GRAB,
  RIGHT,
  LEFT,
  UNDEFINED
};

class Scene {
private:
public:
  std::vector< Box > box; // Array of boxes
  std::vector< Box > result; // Array of boxes
  std::vector< std::vector<int> > functions; // Functions with array of commands
  /*
  1: GoLeft(), Grab(), CallFunc2(), GoRight();
  2: GoRight(), Grab(), GoLeft()
  3:

  First we go left and grab, then we call 2
  When we call 2, we put (1, 4) in the stack;
  Now we execute 2, GoRight, Grab, Goleft and then re return to the stack and continues on from last position. 
  When we reach the end of 1. function we check next in stack. 
  If stack is empty, we return and check if result is correct.
  */
  std::vector<Pos> stack; // Call last in this when current function reaches end;
  Crane crane;
  int height;
  int width; // Scene Width

  void Init(int height, int width, std::vector<Box> start, std::vector<Box> result, std::vector<  std::vector<int> > funcs);
  int Tick(); // Returns false if this was last tick;
  bool IsDone();
  int CallFunc(int func);
};

#endif
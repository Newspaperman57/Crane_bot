#include "scene.h"

void Scene::Init(int height, int width, std::vector<Box> start, std::vector<Box> result, std::vector<  std::vector<int> > funcs) {
  // Fill variables
  crane.Init();
  box = start;
  functions = funcs;
  for (int i = 0; i < (int)funcs.size(); i++) {
    functions[i][funcs[i].size()] = UNDEFINED;
  }
  
  this->result = result;
  this->height = height;
  this->width = width;

  stack.push_back((Pos){0,0});
}

int Scene::Tick() { // Returns false if this was last tick
  // If the stack is empty or we have succeeded, return false
  if(IsDone())
    return (int)SUCCES;
  if(stack.empty())
      return (int)FAILURE;

  // Go to stack and execute last entry if not null-pointer. If null-pointer, remove and take next. If stack is empty, return false.
  while(functions[stack.back().x][stack.back().y] == UNDEFINED) { // Find entry which is not null-pointer
    stack.pop_back();
    if(stack.empty())
      return FAILURE;
  }
  
  // Execute function
  int returnValue = CallFunc(functions[stack.back().x][stack.back().y]);
  // (x, y+1) into stack.
  stack.back().y++;

  // If return is not -1, put (return, 0) into stack;
  if(returnValue != -1)
    stack.push_back((Pos){returnValue, 0});

  return (int)NOT_DONE;
}

int Scene::CallFunc(int func) {
  switch(func) {
    case FUNC1:
      printf("Call function 1\n");
      return 1;
      break;
    case FUNC2:
      return 2;
      break;
    case FUNC3:
      return 3;
      break;
    case FUNC4:
      return 4;
      break;
    case FUNC5:
      return 5;
      break;
    case GRAB:
      printf("Grab\n");
      crane.Grab(&box, height);
      break;
    case RIGHT:
      printf("Go Right\n");
      crane.GoRight();
      break;
    case LEFT:
      printf("Go Left\n");
      crane.GoLeft();
      break;
  }
  return -1;
}
bool Scene::IsDone() {
  // Go though box and compare to result and if all boxes have corrosponding box at the position, return true
  bool foundOne;
  for(int i = 0; i < (int)box.size(); i++) {
    printf("Box at: %d x %d\n", box[i].pos.x, box[i].pos.y );
  }
  for(int i = 0; i < (int)box.size(); i++) {
    foundOne = false;
    for(int j = 0; j < (int)result.size(); j++) {
      if(compare(box[i], result[j]))
        foundOne = true;
    }
    if(!foundOne) {
      return false;
    }
  }
  return true;
}
#include "scene.h"

void Scene::Init(int height, int width, std::vector<Box> start, std::vector<Box> result, std::vector<  std::vector<int> > funcs) {
  // Fill variables
  crane.Init();
  box = start;
  functions = funcs;
  for (int i = 0; i < (int)funcs.size(); i++) {
    if(funcs[i].size() > 0)
      functions[i].push_back(UNDEFINED);
  }
  
  this->result = result;
  this->height = height;
  this->width = width;

  stack.push_back((Pos){0,0});
}

int Scene::Tick(int* currFunction, int* currTask) {
  if(IsDone())
    return (int)SUCCES;

  if(stack.empty())
      return (int)FAILURE;

  // Go to stack and execute last entry if not null-pointer. If null-pointer, remove and take next. If stack is empty, return false.
  while(functions[stack.back().x][stack.back().y] == UNDEFINED) { // Find entry which is not undefined
    stack.pop_back();
    if(stack.empty())
      return FAILURE; // No more commmands. We already checked if we solved the task, so we return FAILURE
  }
  
  *currFunction = stack.back().x;
  *currTask = stack.back().y;
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
      return 0;
      break;
    case FUNC2:
      printf("Call function 2\n");
      return 1;
      break;
    case FUNC3:
      printf("Call function 3\n");
      return 2;
      break;
    case FUNC4:
      printf("Call function 4\n");
      return 3;
      break;
    case FUNC5:
      printf("Call function 5\n");
      return 4;
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
    foundOne = false;
    for(int j = 0; j < (int)result.size(); j++) {
      if(box[i].compare(result[j]))
        foundOne = true;
    }
    if(!foundOne) {
      return false;
    }
  }
  return true;
}
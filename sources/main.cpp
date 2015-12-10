#include <iostream>

#include "scene.h"
#include "box.h"

int main() {
  Scene scene;
  std::vector<Box> start;
  std::vector<Box> result;
  std::vector<  std::vector<int> > functions;
  functions.resize(2);

  functions[0].push_back(FUNC1);
  functions[0].push_back(FUNC1);
  
  functions[1].push_back(GRAB);
  functions[1].push_back(RIGHT);
  functions[1].push_back(GRAB);
  functions[1].push_back(LEFT);

  start.push_back((Box){1,0});
  start.push_back((Box){2,0});

  result.push_back((Box){1,1});
  result.push_back((Box){2,1});

  scene.Init(4, 2, start, result, functions); 
  int res;
  for(int i = 0; i < 20; i++) {
    res = scene.Tick();
    if(res == SUCCES) {
      printf("YOU WON!\n");
      i = 20;
    } else if(res == FAILURE) {
      printf("YOU LOST!\n");
      i = 20;
    }
  }
  return 0;
}
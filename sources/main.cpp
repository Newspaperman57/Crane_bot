#include <cstdio>
#include <string>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>

#include "scene.h"
#include "box.h"
#include "draw.h"

#define SCREENSIZEX 720
#define SCREENSIZEY 480
#define CRATE_SIZE 60

SDL_Window* Window;
SDL_Renderer* Renderer;

void Init() { 
    SDL_Init( SDL_INIT_VIDEO );
    SDL_CreateWindowAndRenderer(SCREENSIZEX, SCREENSIZEY, SDL_WINDOW_SHOWN, &Window, &Renderer );

    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
      printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() ); 
    }
}

int main() {
  // Init SDL
  printf("Initializing SDL\n");
  Init();
  //SDL_RenderClear(Renderer);  

  // SDL_CreateTextureFromSurface(Renderer, crateS);
  SDL_Texture* crateT = IMG_LoadTexture(Renderer, "gfx/crate.png"); 
  SDL_Texture* craneT = IMG_LoadTexture(Renderer, "gfx/crane.png"); 
  if(crateT == NULL || craneT == NULL)  {
     printf("ERROR: %s", SDL_GetError());
  }
  int sceneHeigth = 8;
  int sceneWidth = 3;

  // Scene and crane stuff
  Scene scene;
  std::vector<Box> start;
  std::vector<Box> result;
  std::vector<  std::vector<int> > functions;
  functions.resize(4);

  functions[0].push_back(FUNC2);
  functions[0].push_back(FUNC3);
  functions[0].push_back(FUNC1);
  
  functions[1].push_back(GRAB);
  functions[1].push_back(RIGHT);
  functions[1].push_back(FUNC4);
  
  functions[2].push_back(FUNC4);
  functions[2].push_back(GRAB);
  functions[2].push_back(RIGHT);
  
  functions[3].push_back(GRAB);
  functions[3].push_back(LEFT);

  start.push_back((Box){1,1});
  start.push_back((Box){2,1});
  start.push_back((Box){3,1});
  start.push_back((Box){4,1});
  start.push_back((Box){5,1});
  start.push_back((Box){6,1});

  result.push_back((Box){4,0});
  result.push_back((Box){5,0});
  result.push_back((Box){6,0});
  result.push_back((Box){4,2});
  result.push_back((Box){5,2});
  result.push_back((Box){6,2});

  scene.Init(sceneHeigth, sceneWidth, start, result, functions); 

  scene.crane.pos.y = 1;

  int res = NOT_DONE;
  int function, task;
  bool quit = false; 
  SDL_Event e;
  
  SDL_Rect cratePos;
    cratePos.w = CRATE_SIZE;
    cratePos.h = CRATE_SIZE;

  SDL_Rect crateBasePos;
    crateBasePos.x = 30;
    crateBasePos.y = 20;
    crateBasePos.w = CRATE_SIZE;
    crateBasePos.h = CRATE_SIZE;

  SDL_Rect cranePos;
    cranePos.x = 30;
    cranePos.y = 200;
    cranePos.w = 80;
    cranePos.h = 76;

  SDL_Rect rect;
    rect.x = 20;
    rect.y = crateBasePos.y+CRATE_SIZE*(sceneHeigth-1);
    rect.w = 80;
    rect.h = 40;
    printf("Rect y: %d\n", rect.y);
  SDL_Rect basePos = rect;

  printf("Main Loop!\n");
  while(!quit) {
    if(res == NOT_DONE) {
      res = scene.Tick( &function, &task);
    } else if(res == SUCCES) {
      printf("YOU WON\n");
      res = DONE;
    } else if(res == FAILURE) {
      printf("YOU LOST!\n");
      res = DONE;
    }
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 ) {
      //User requests quit
      if( e.type == SDL_QUIT ) {
          quit = true;
      }
      //User presses a key
      else if( e.type == SDL_KEYDOWN )
      {
        //Select surfaces based on key press
        switch( e.key.keysym.sym )
        {
          case SDLK_UP:
            printf("UP pressed!\n");
          break;
        }
      }
    }
    // Render box's in grid
    for (int i = 0; i < (int)scene.box.size(); ++i) {
      if(scene.box[i].pos.x == 0) // Box is in crane, so use that pos
        cratePos.x = crateBasePos.x+(CRATE_SIZE+40)*(scene.crane.pos.y);
      else 
        cratePos.x = crateBasePos.x+(CRATE_SIZE+40)*(scene.box[i].pos.y);
      cratePos.y = crateBasePos.y-CRATE_SIZE*(-scene.box[i].pos.x);
      SDL_RenderCopy( Renderer, crateT, NULL, &cratePos );
    }

    for(int i = 0; i < sceneWidth; i++) {
      basePos.x = rect.x+(CRATE_SIZE+40)*i;
      Draw::FilledRectangleRoundEdge(Renderer, basePos, 10);
    }
    

    cranePos.x = crateBasePos.x+(CRATE_SIZE+40)*(scene.crane.pos.y)-10;
    cranePos.y = crateBasePos.y-CRATE_SIZE*(-scene.crane.pos.x)-20;

    SDL_RenderCopy(Renderer, craneT, NULL, &cranePos );
    //Apply the image
    //SDL_RenderCopy( Renderer, crateT, NULL, &cratePos );
    //SDL_RenderCopy( Renderer, crateT, NULL, &cratePos2);
    
    SDL_RenderPresent(Renderer);
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderClear(Renderer);
    SDL_SetRenderDrawColor(Renderer, 100, 0, 0, 0);
    SDL_Delay(750);
  }

  SDL_DestroyRenderer( Renderer );
  SDL_DestroyWindow( Window );

  SDL_Quit();
  return 0;
}

/*

Draw grid
Read box's positions
Render box's in grid

*/
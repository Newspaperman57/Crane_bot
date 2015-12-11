#ifndef __DRAW
#define __DRAW

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Draw {
private:
public:
  static void Rectangle(SDL_Renderer* renderer, SDL_Rect rectangle, int thickness);
  static void RectangleRoundEdge(SDL_Renderer* renderer, SDL_Rect rectangle, int radius, int thickness);
  static void FilledRectangleRoundEdge(SDL_Renderer* renderer,  SDL_Rect rectangle, int radius);
  static void FilledCircle(SDL_Renderer* Renderer, int cx, int cy, int radius);
  static void Circle(SDL_Renderer* renderer, int n_cx, int n_cy, int radius);
  static void CircleKvadrant(SDL_Renderer* renderer, int n_cx, int n_cy, int radius, int kvadrant);
};

#endif
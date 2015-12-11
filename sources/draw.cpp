#include "draw.h"

void Draw::Rectangle(SDL_Renderer* renderer, SDL_Rect rectangle, int thickness) {
  SDL_RenderFillRect( renderer, &rectangle );
}

void Draw::FilledRectangleRoundEdge(SDL_Renderer* renderer,  SDL_Rect rectangle, int radius) {
  // Draw inner rectangle
  SDL_Rect inner = rectangle;
  inner.x += radius;
  inner.y += radius;
  inner.w -= radius*2;
  inner.h -= radius*2;
  SDL_RenderFillRect( renderer, &inner );
  
  // Draw outer
  SDL_Rect left = rectangle;
  left.y += radius;
  left.w = radius;
  left.h -= radius*2;
  SDL_RenderFillRect( renderer, &left );
  
  SDL_Rect right = rectangle;
  right.x += rectangle.w-(radius);
  right.y += radius;
  right.w = radius;
  right.h -= radius*2;
  SDL_RenderFillRect( renderer, &right );
  
  SDL_Rect up = rectangle;
  up.x += radius;
  up.w = rectangle.w-radius*2;
  up.h = radius;
  SDL_RenderFillRect( renderer, &up );
  
  SDL_Rect down = rectangle;
  down.y += rectangle.h-radius;
  down.x += radius;
  down.w = rectangle.w-radius*2;
  down.h = radius;
  SDL_RenderFillRect( renderer, &down );
  // Draw circles
  FilledCircle(renderer, rectangle.x+radius, rectangle.y+radius, radius);
  FilledCircle(renderer, rectangle.x+radius, rectangle.y+rectangle.h-radius, radius);
  FilledCircle(renderer, rectangle.x+rectangle.w-radius, rectangle.y+radius, radius);
  FilledCircle(renderer, rectangle.x+rectangle.w-radius, rectangle.y+rectangle.h-radius, radius);
}

void Draw::FilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius)
{
    for (double dy = 1; dy <= radius; dy += 1.0)
    {
        double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
        int x = cx - dx;

        for (; x <= cx + dx; x++)
        {
            SDL_RenderDrawPoint(renderer, x, (cy + radius - dy)); //Renders on middle of screen.
            SDL_RenderDrawPoint(renderer, x, (cy - radius + dy)); //Renders on middle of screen.
        }
    }
}

void Draw::Circle(SDL_Renderer* renderer, int n_cx, int n_cy, int radius)
{
    // if the first pixel in the screen is represented by (0,0) (which is in sdl)
    // remember that the beginning of the circle is not in the middle of the pixel
    // but to the left-top from it:
 
    double error = (double)-radius;
    double x = (double)radius -0.5;
    double y = (double)0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5;
 
    while (x >= y)
    {
        SDL_RenderDrawPoint(renderer, (int)(cx + x), (int)(cy + y));
        SDL_RenderDrawPoint(renderer, (int)(cx + y), (int)(cy + x));
 
        if (x != 0)
        {
            SDL_RenderDrawPoint(renderer, (int)(cx - x), (int)(cy + y));
            SDL_RenderDrawPoint(renderer, (int)(cx + y), (int)(cy - x));
        }
 
        if (y != 0)
        {
            SDL_RenderDrawPoint(renderer, (int)(cx + x), (int)(cy - y));
            SDL_RenderDrawPoint(renderer, (int)(cx - y), (int)(cy + x));
        }
 
        if (x != 0 && y != 0)
        {
            SDL_RenderDrawPoint(renderer, (int)(cx - x), (int)(cy - y));
            SDL_RenderDrawPoint(renderer, (int)(cx - y), (int)(cy - x));
        }
 
        error += y;
        ++y;
        error += y;
 
        if (error >= 0)
        {
            --x;
            error -= x;
            error -= x;
        }
    }
}

void Draw::CircleKvadrant(SDL_Renderer* renderer, int n_cx, int n_cy, int radius, int kvadrant) {
    double error = (double)-radius;
    double x = (double)radius -0.5;
    double y = (double)0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5;
 
    while (x >= y)
    {
        if(kvadrant == 1) {
          SDL_RenderDrawPoint(renderer, (int)(cx + y), (int)(cy - x));
          SDL_RenderDrawPoint(renderer, (int)(cx + x), (int)(cy - y));
        } else if(kvadrant == 2) {
          SDL_RenderDrawPoint(renderer, (int)(cx - y), (int)(cy - x));
          SDL_RenderDrawPoint(renderer, (int)(cx - x), (int)(cy - y));
        } else if(kvadrant == 3) {
          SDL_RenderDrawPoint(renderer, (int)(cx - y), (int)(cy + x));
          SDL_RenderDrawPoint(renderer, (int)(cx - x), (int)(cy + y));
        } else if(kvadrant == 4) {
          SDL_RenderDrawPoint(renderer, (int)(cx + y), (int)(cy + x));
          SDL_RenderDrawPoint(renderer, (int)(cx + x), (int)(cy + y));
        }
        error += y;
        ++y;
        error += y;
        if (error >= 0)
        {
            --x;
            error -= x;
            error -= x;
        }
    }
}

void Draw::RectangleRoundEdge(SDL_Renderer* renderer, SDL_Rect rectangle, int radius, int thickness) {
  // Draw lines
  // Top
  SDL_RenderDrawLine(renderer, rectangle.x+radius, rectangle.y, rectangle.x+rectangle.w-radius, rectangle.y);
  // Bottom
  SDL_RenderDrawLine(renderer, rectangle.x+radius, rectangle.y+rectangle.h, rectangle.x+rectangle.w-radius, rectangle.y+rectangle.h);
  // Left
  SDL_RenderDrawLine(renderer, rectangle.x, rectangle.y+radius, rectangle.x, rectangle.y+rectangle.h-radius);
  // Right
  SDL_RenderDrawLine(renderer, rectangle.x+rectangle.w, rectangle.y+radius, rectangle.x+rectangle.w, rectangle.y+rectangle.h-radius);
  
  // Draw kvadrants/round edges
  Draw::CircleKvadrant(renderer, rectangle.x+rectangle.w-radius, rectangle.y+radius            , radius, 1);
  Draw::CircleKvadrant(renderer, rectangle.x+radius            , rectangle.y+radius            , radius, 2);
  Draw::CircleKvadrant(renderer, rectangle.x+radius            , rectangle.y+rectangle.h-radius, radius, 3);
  Draw::CircleKvadrant(renderer, rectangle.x+rectangle.w-radius, rectangle.y+rectangle.h-radius, radius, 4);
  if(thickness != 1) {
    rectangle.x += 1;
    rectangle.y += 1;
    rectangle.w -= 2;
    rectangle.h -= 2;
    RectangleRoundEdge(renderer, rectangle, radius-1, thickness-1);
  }
}
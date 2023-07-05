#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class WindowHandler {
 public:
  WindowHandler();

 private:
  int WIDTH = 800;
  int HEIGHT = 600;

  int START_X = 32;
  int START_Y = 32;

  SDL_Window *window

};
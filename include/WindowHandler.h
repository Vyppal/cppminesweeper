#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <math.h>

#include "GameHandler.h"

// depending on implementation of game handler, could be removed
#include "Tile.h"

class WindowHandler {
 public:
  WindowHandler(GameHandler *gameHandler);

  int EventHandler();
  void UpdateSprites();
  void End();

  void UpdateMineCount(int minesRemaining);
  
  bool GetLeftMouseButtonUp();
  bool GetRightMouseButtonUp();
  bool GetMiddleMouseButtonUp();
  bool GetMiddleMouseButton();

  void UpdateWindow();
  
  std::vector<int> GetBoardRelativeMousePos();

 private:
  GameHandler *_gameHandler;
  int WIDTH = 800;
  int HEIGHT = 600;

  int START_X = 32;
  int START_Y = 32;

  int TILE_SIZE = 32;

  SDL_Window *window;
  SDL_Surface *windowSurface = NULL;

  int mouseX = 0, mouseY = 0;
  int mouseButtonState = SDL_GetMouseState(&mouseX, &mouseY);

  std::string mouseButState = std::bitset<5>(mouseButtonState).to_string();
  std::string prevMouseButState;

  TTF_Font* font = NULL;
  SDL_Color minesRemainingColour = {255, 0, 0};
  SDL_Renderer *renderer = NULL;
  SDL_Surface *minesRemainingSurface = NULL;
};
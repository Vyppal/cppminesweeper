#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Board.h"
#include "GameHandler.h"
#include "WindowHandler.h"


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 10;

const int TILE_SIZE = 32;
const int START_X = 32;
const int START_Y = 32;


GameHandler gameHandler{};
WindowHandler windowHandler{&gameHandler};

int main(int argc, char* argv[]) {
  bool runGame = true;

  do {
    switch (windowHandler.EventHandler()) {
      case 1:
        runGame = false;
       break;
      default:
       break;
    };
    windowHandler.UpdateSprites();
  } while (runGame);

  windowHandler.End();

	return EXIT_SUCCESS;
}
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Tile.h"
#include "GameHandler.h"

const int WIDTH = 800, HEIGHT = 600;

Tile tile{10, 20};
bool xx = tile.GetIsOpen();

int main(int argc, char* argv[]) {
  SDL_Init( SDL_INIT_EVERYTHING );
  SDL_Window *window = SDL_CreateWindow("minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

  if (NULL == window) {
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    return 1;
  }
  SDL_Event windowEvent;

  std::cout << xx << std::endl;

  while (true) {
    if (SDL_PollEvent(&windowEvent)) {
      if (SDL_QUIT == windowEvent.type) {  break;  }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
	return EXIT_SUCCESS;
}
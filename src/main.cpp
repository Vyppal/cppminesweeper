#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Tile.h"
#include "GameHandler.h"
#include "Board.h"


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 10;

const int TILE_SIZE = 32;
const int START_X = 32;
const int START_Y = 32;


GameHandler gameHandler{};
BoardData boardData{BOARD_WIDTH, BOARD_HEIGHT, 4};
Board board{boardData, &gameHandler};


	



int main(int argc, char* argv[]) {
  SDL_Init( SDL_INIT_EVERYTHING );
  SDL_Window *window = SDL_CreateWindow("minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

  SDL_Surface *imageSurface = NULL;
  SDL_Surface *windowSurface = NULL;

  if (NULL == window) {
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    return 1;
  }
  windowSurface = SDL_GetWindowSurface( window );
  SDL_Event windowEvent;
  if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) {
    std::cout << "Could not create window: " << IMG_GetError( ) << std::endl;
    return 1;
  }

  imageSurface = IMG_Load("res/textures/mine.png");
  if ( NULL == imageSurface ){
    std::cout << "SDL could not load image! SDL Error: " << SDL_GetError( ) << std::endl;
  }

  while (true) {
    if (SDL_PollEvent(&windowEvent)) {
      if (SDL_QUIT == windowEvent.type) {  break;  }
    }
    SDL_BlitScaled( imageSurface, NULL, windowSurface, new SDL_Rect{160, 120, 320, 240} );
    SDL_UpdateWindowSurface( window );
  }

  SDL_FreeSurface( imageSurface );
  SDL_FreeSurface( windowSurface );
    
  imageSurface = NULL;
  windowSurface = NULL;

  SDL_DestroyWindow(window);
  SDL_Quit();
	return EXIT_SUCCESS;
}
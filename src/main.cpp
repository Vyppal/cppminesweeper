#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Tile.h"
#include "GameHandler.h"
#include "Board.h"
// #include "SpriteHandler.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 10;

const int TILE_SIZE = 32;
const int START_X = 32;
const int START_Y = 32;

GameConfig gameConfig{
  32
};




int main(int argc, char* argv[]) {
  GameHandler gameHandler{gameConfig};
  BoardData boardData{BOARD_WIDTH, BOARD_HEIGHT, 4};
  Board board{boardData, &gameHandler};

  SDL_Window *window = SDL_CreateWindow("minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);


  // SpriteHandler spriteHandler{window, &gameHandler};
  SDL_Init( SDL_INIT_EVERYTHING );
  SDL_Surface *windowSurface = SDL_GetWindowSurface( window );
  if (NULL == window) {   std::cout << "Could not create window: " << SDL_GetError() << std::endl;   return 1;   }

  SDL_Event windowEvent;
  // SDL_Rect dest;
  // dest.x = 160;
	// dest.y = 120;
	// dest.w = 320;
	// dest.h = 240;
  SDL_Surface *imageSurface = IMG_Load("res/textures/inactive.png");
  SDL_BlitScaled( imageSurface, NULL, windowSurface, NULL);

  if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) {   std::cout << "Could not create window: " << IMG_GetError( ) << std::endl;   return 1;   }


  for (int i = 0; i < board.GetBoard().size(); i++) {
   for (int j = 0; j < board.GetBoard()[i].size(); j++) {
      // Tile tile = board.GetBoard()[i][j];
      int xxPos = board.GetBoard()[i][j].GetXPos();
      int yyPos = board.GetBoard()[i][j].GetYPos();
      // SDL_Rect dest{xxPos * TILE_SIZE, yyPos * TILE_SIZE, TILE_SIZE, TILE_SIZE};

      // // std::string imagePath = GetSprite(tile);
      // // SDL_Surface *imageSurface = IMG_Load(("res/textures/" + imagePath).c_str());
      // SDL_Surface *imageSurface = IMG_Load("res/textures/inactive.png");

      // if (imageSurface == NULL) {   std::cout << "SDL could not load image! SDL Error: " << SDL_GetError( ) << std::endl;   return 1;   }
      // int blitResult = SDL_BlitScaled(imageSurface, NULL, windowSurface, &_tileRect);
      // if (blitResult < 0) {   std::cout << "blit failed" << std::endl;   }
    }
  }


  while (true) {
    if (SDL_PollEvent(&windowEvent)) {
      if (SDL_QUIT == windowEvent.type) {  break;  }
    }
    SDL_UpdateWindowSurface( window );
  }


  SDL_DestroyWindow(window);
  SDL_Quit();
	return EXIT_SUCCESS;
}
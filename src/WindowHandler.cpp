#include "WindowHandler.h"

WindowHandler::WindowHandler(GameHandler *gameHandler) : _gameHandler(gameHandler){
  SDL_Init( SDL_INIT_EVERYTHING );
  window = SDL_CreateWindow("minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
  if (window == NULL) {
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    return;
  }
  windowSurface = SDL_GetWindowSurface(window);
  if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    std::cout << "Could not create window: " << IMG_GetError() << std::endl;
    return;
  }
}

int WindowHandler::EventHandler() {
  mouseButtonState = SDL_GetMouseState(&mouseX, &mouseY);

  prevMouseButState = mouseButState;
  mouseButState = std::bitset<5>(mouseButtonState).to_string();

  
  std::vector<int> boardMousePos = GetBoardRelativeMousePos();
  if (boardMousePos.at(0) != -1) {
    ClickType clickType = ClickType::kNone;
    if (GetLeftMouseButtonUp()) {   clickType = ClickType::kLeftMouse;   }
    else if (GetRightMouseButtonUp()) {   clickType = ClickType::kRightMouse;   }
    else if (GetMiddleMouseButtonUp()) {   clickType = ClickType::kMiddleMouse;   }
    else if (GetMiddleMouseButton()) {   clickType = ClickType::kMiddleMouseHold;   }
    _gameHandler->RegisterClick(boardMousePos, clickType);
  }

  SDL_Event windowEvent;
  if (SDL_PollEvent(&windowEvent)) {
    if (SDL_QUIT == windowEvent.type) {
      return 1; // break code
    }
  }
  return 0;
}

void WindowHandler::UpdateSprites() {
  std::vector<std::vector<Tile>> *board = _gameHandler->GetBoard()->GetBoard();
  for (int rowNum = 0; rowNum < board->size(); rowNum++) {
    std::vector<Tile> row = board->at(rowNum);
    for (int tileNum = 0; tileNum < row.size(); tileNum++) {
      Tile tile = row[tileNum];
      tile.FinalizeTile();
      SDL_Surface *imageSurface = IMG_Load(("res/textures/" + tile.GetSprite()).c_str());
      if (imageSurface == NULL) {   std::cout << "SDL could not load image! SDL Error: " << SDL_GetError() << std::endl;   return;   }
      SDL_BlitScaled(imageSurface, NULL, windowSurface, new SDL_Rect{START_X + tile.GetXPos() * TILE_SIZE, START_Y + tile.GetYPos() * TILE_SIZE, TILE_SIZE, TILE_SIZE});
      // SDL_FreeSurface(imageSurface);
      // imageSurface = NULL;
    }
  }
  SDL_UpdateWindowSurface( window );
}


void WindowHandler::End() {
  SDL_FreeSurface(windowSurface);
  windowSurface = NULL;
  SDL_DestroyWindow(window);
  SDL_Quit();
}



bool WindowHandler::GetLeftMouseButtonUp() {
  if (prevMouseButState[4] == '1'){   return mouseButState[4] == '0';   }
  return false;
}

bool WindowHandler::GetRightMouseButtonUp() {
  if (prevMouseButState[2] == '1'){   return mouseButState[2] == '0';   }
  return false;
}

bool WindowHandler::GetMiddleMouseButtonUp() {
  if (prevMouseButState[3] == '1'){   return mouseButState[3] == '0';   }
  return false;
}

bool WindowHandler::GetMiddleMouseButton() {
  return mouseButState[3] == '1';
}

std::vector<int> WindowHandler::GetBoardRelativeMousePos() {
  std::vector<int> boardDimensions = _gameHandler->GetBoardDimensions();
  int bottomRightX = START_X + TILE_SIZE * boardDimensions.at(0);
  int bottomRightY = START_Y + TILE_SIZE * boardDimensions.at(1);

  if (START_X <= mouseX && mouseX<= bottomRightX) {
    if (START_Y <= mouseY && mouseY <= bottomRightY) {
      return std::vector<int>{
        static_cast<int>(floor((mouseX - START_X) / TILE_SIZE)),
        static_cast<int>(floor((mouseY - START_Y) / TILE_SIZE))
      }; 
    }
  }
  return std::vector<int>{-1, -1};
  
}
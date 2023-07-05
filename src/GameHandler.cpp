#include "GameHandler.h"

GameHandler::GameHandler() {};

void GameHandler::SendActiveMineRequest() {
  _isMineActive = true;
}

Board *GameHandler::GetBoard() {
  return &board;
}

void GameHandler::RegisterClick(std::vector<int> boardPos, ClickType clickType) {
  switch (clickType) {
    case ClickType::kLeftMouse:
      {
        int wasMine = board.GetBoard()->at(boardPos.at(1)).at(boardPos.at(0)).OpenTile();
      // The if statement also calls the function to open tile
      if (wasMine == 1) {   SendActiveMineRequest();   }
     break;
     }
    case ClickType::kRightMouse:
      board.GetBoard()->at(boardPos.at(1)).at(boardPos.at(0)).SwitchFlagTileState();
     break;
    case ClickType::kMiddleMouse:
      board.OpenTileGroup(Position{boardPos.at(0), boardPos.at(1)});
     break;
    case ClickType::kMiddleMouseHold:
      board.SchrodingerTiles(Position{boardPos.at(0), boardPos.at(1)});
     break;
    
  }
}


std::vector<int> GameHandler::GetBoardDimensions() {
  return std::vector<int>(boardWidth, boardHeight);
}
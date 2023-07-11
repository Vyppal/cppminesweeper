#include "GameHandler.h"

GameHandler::GameHandler() {};

void GameHandler::SendActiveMineRequest() {
  _isMineActive = true;
  board.OpenAllMines();
}

Board *GameHandler::GetBoard() {
  return &board;
}

void GameHandler::RegisterClick(std::vector<int> boardPosition, ClickType clickType) {
  Position boardPos{boardPosition.at(0), boardPosition.at(1)};
  int var = 0;
  switch (clickType) {
    case ClickType::kLeftMouse:
      { // var acts as a variable named "wasMine"
        if (!firstClick) {
          var = board.OpenTile(boardPos);
          if (var != 1) {   break;   }
          SendActiveMineRequest();
         break;
        }
        board.MoveAdjacentMines(boardPos);
        firstClick = false;
        var = board.OpenTile(boardPos);
        if (var == 1) {   SendActiveMineRequest();   }
       break;
      }
    case ClickType::kRightMouse:
      { // var acts as a variable named "minesRemainingIncrementValue"
        var = board.GetBoard()->at(boardPos.y).at(boardPos.x).SwitchFlagTileState();
        minesRemaining += var;
       break;
      }
    case ClickType::kMiddleMouse:
      { // var acts as a variable named "wasMine"
        var = board.OpenTileGroup(boardPos);
        if (var == 1) {   SendActiveMineRequest();   }
       break;
      }
    case ClickType::kMiddleMouseHold:
      if (prevBoardPos.x != boardPos.x && prevBoardPos.y != boardPos.y) {
        board.UnSchrodingerTiles(prevSchrodingeredTilePos);
      }
      board.SchrodingerTiles(boardPos);
      activeSchrodinger = true;
      prevSchrodingeredTilePos = boardPos;
     break;
  }
  prevBoardPos = boardPos;
  if (activeSchrodinger && clickType != ClickType::kMiddleMouseHold) {
    activeSchrodinger = false;
    board.UnSchrodingerTiles(prevSchrodingeredTilePos);
  }
}


int GameHandler::GetMinesRemaining() {
  return minesRemaining;
}

std::vector<int> GameHandler::GetBoardDimensions() {
  return std::vector<int>(boardWidth, boardHeight);
}
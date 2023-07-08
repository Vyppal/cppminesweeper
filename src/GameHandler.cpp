#include "GameHandler.h"

GameHandler::GameHandler() {};

void GameHandler::SendActiveMineRequest() {
  _isMineActive = true;
  board.OpenAllMines();
}

Board *GameHandler::GetBoard() {
  return &board;
}

void GameHandler::RegisterClick(std::vector<int> boardPos, ClickType clickType) {
  int var = 0;
  switch (clickType) {
    case ClickType::kLeftMouse:
      { // var acts as a variable named "wasMine"
        var = board.OpenTile(Position{boardPos.at(0), boardPos.at(1)});
        if (var == 1) {   SendActiveMineRequest();   }
       break;
      }
    case ClickType::kRightMouse:
      { // var acts as a variable named "minesRemainingIncrementValue"
        var = board.GetBoard()->at(boardPos.at(1)).at(boardPos.at(0)).SwitchFlagTileState();
        minesRemaining += var;
       break;
      }
    case ClickType::kMiddleMouse:
      { // var acts as a variable named "wasMine"
        var = board.OpenTileGroup(Position{boardPos.at(0), boardPos.at(1)});
        if (var == 1) {   SendActiveMineRequest();   }
       break;
      }
    case ClickType::kMiddleMouseHold:
      if (prevBoardPos != boardPos) {
        board.UnSchrodingerTiles(Position{prevSchrodingeredTilePos.at(0), prevSchrodingeredTilePos.at(1)});
      }
      board.SchrodingerTiles(Position{boardPos.at(0), boardPos.at(1)});
      activeSchrodinger = true;
      prevSchrodingeredTilePos = boardPos;
     break;
  }
  prevBoardPos = boardPos;
  if (activeSchrodinger && clickType != ClickType::kMiddleMouseHold) {
    activeSchrodinger = false;
    board.UnSchrodingerTiles(Position{prevSchrodingeredTilePos.at(0), prevSchrodingeredTilePos.at(1)});
  }
}


int GameHandler::GetMinesRemaining() {
  return minesRemaining;
}

std::vector<int> GameHandler::GetBoardDimensions() {
  return std::vector<int>(boardWidth, boardHeight);
}
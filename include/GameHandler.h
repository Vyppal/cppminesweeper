#pragma once

#include "Board.h"

#include <vector>
#include <iostream>

enum ClickType {
  kLeftMouse,
  kRightMouse,
  kMiddleMouse,
  kMiddleMouseHold,
  kNone
};

class GameHandler {
 public:
  GameHandler();
  
  void SendActiveMineRequest();
  Board *GetBoard();

  std::vector<int> GetBoardDimensions();
  
  void RegisterClick(std::vector<int> boardPos, ClickType clickType);


 private:
  bool _isGameOver = false;
  bool _isMineActive = false;
  int boardWidth = 10;
  int boardHeight = 10;
  BoardData boardData{boardWidth, boardHeight, 4};
  Board board{boardData};

  std::vector<int> prevSchrodingeredTilePos{-1, -1};
  std::vector<int> prevBoardPos{-1, -1};
  bool activeSchrodinger = false;


};
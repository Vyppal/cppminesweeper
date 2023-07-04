#pragma once

#include "Tile.h"
#include <vector>
#include "GameHandler.h"


struct BoardData {
  int width;
  int height;
  double mineDensity;
};

struct Position {
  int x;
  int y;
};

class Board {
 public:
  Board(BoardData boardData, GameHandler *gameHandler);

  void CreateNewBoard(BoardData boardData);
  std::vector<std::vector<Tile>> GetBoard();
  std::vector<Position> GetAdjacentTileCoordinates(Position tilePosition);


 private:
  BoardData _boardData;
  GameHandler *_gameHandler;
  std::vector<std::vector<Tile>> _board;
};
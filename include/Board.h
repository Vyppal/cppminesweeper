#pragma once

#include "Tile.h"
#include <vector>

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
  Board(BoardData boardData);

  void CreateNewBoard(BoardData boardData);
  std::vector<std::vector<Tile>> *GetBoard();
  std::vector<Position> GetAdjacentTileCoordinates(Position tilePosition);

  void SchrodingerTiles(Position epicentre);
  void UnSchrodingerTiles(Position epicentre);
  int OpenTileGroup(Position epicentre);

  int OpenTile(Position tilePosition);

  void OpenAllMines();

 private:
  BoardData _boardData;
  std::vector<std::vector<Tile>> _board;
  std::vector<Position> _unprocessedZeros;
};
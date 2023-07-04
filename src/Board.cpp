#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

std::vector<Position> Board::GetAdjacentTileCoordinates(Position tilePosition) {
  std::vector<Position> adjacentPositions;

  bool leftBound = tilePosition.x - 1 < 0;
  bool rightBound = tilePosition.x + 1 >= _boardData.width;
  bool topBound = tilePosition.y - 1 < 0;
  bool bottomBound = tilePosition.y + 1 >= _boardData.height;

  if (!leftBound) {
    adjacentPositions.push_back(Position{tilePosition.x - 1, tilePosition.y});
    if (!topBound) {
      adjacentPositions.push_back(Position{tilePosition.x - 1, tilePosition.y - 1});
    }
    if (!bottomBound) {
      adjacentPositions.push_back(Position{tilePosition.x - 1, tilePosition.y + 1});
    }
  }
  if (!rightBound) {
    adjacentPositions.push_back(Position{tilePosition.x + 1, tilePosition.y});
    if (!topBound) {
      adjacentPositions.push_back(Position{tilePosition.x + 1, tilePosition.y - 1});
    }
    if (!bottomBound) {
      adjacentPositions.push_back(Position{tilePosition.x + 1, tilePosition.y + 1});
    }
  }
  if (!topBound) {
    adjacentPositions.push_back(Position{tilePosition.x, tilePosition.y - 1});
  }
  if (!bottomBound) {
    adjacentPositions.push_back(Position{tilePosition.x, tilePosition.y + 1});
  }
  return adjacentPositions;
}


void Board::CreateNewBoard(BoardData boardData) {
  std::vector<Tile> tempTileList;
  std::vector<Position> allTiles;
  for (int h = 0; h < boardData.height; h++){
    tempTileList.clear();
    for (int w = 0; w < boardData.width; w++){
      Tile newTile{w, h, _gameHandler};
      tempTileList.push_back(newTile);
      Position tilePosition{w, h};
      allTiles.push_back(tilePosition);
    }
    _board.push_back(tempTileList);
  }
  srand((unsigned) time(NULL));
	int randomTileIndex;
  Position activePosition;

  int totalMinesToPlace = allTiles.size() / boardData.mineDensity;

  for (int placedMines = 0; placedMines < totalMinesToPlace; placedMines++) {
    randomTileIndex = rand() % allTiles.size();
    activePosition = allTiles[randomTileIndex];
    _board[activePosition.y][activePosition.x].SetMine();
    allTiles.erase(allTiles.begin() + randomTileIndex);
    std::vector<Position> adjacentPositions = GetAdjacentTileCoordinates(activePosition);
    for (Position pos : adjacentPositions) {
      _board[pos.y][pos.x].AddAdjacentMine();
    }
  }



  // Debugging print grid to console
  std::string line;
  for (auto row : _board) {
    line = "";
    for (auto tile : row) {
      if (tile.GetIsMine()) {
        line += "X ";
      }
      else {
        line += std::to_string(tile.GetTileInformation().adjacentMineCount);
        line += " ";
      }
    }
    std::cout << line << std::endl;
  }
}


Board::Board(BoardData boardData, GameHandler *gameHandler) : _boardData(boardData), _gameHandler(gameHandler) {
  Board::CreateNewBoard(boardData);
}
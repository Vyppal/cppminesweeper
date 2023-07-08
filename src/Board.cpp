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
      Tile newTile{w, h};
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
        line += std::to_string(tile.GetInformation().adjacentMineCount);
        line += " ";
      }
    }
    std::cout << line << std::endl;
  }
}

std::vector<std::vector<Tile>> *Board::GetBoard() {   return &_board;   }



void Board::SchrodingerTiles(Position epicentre) {
  std::vector<Position> adjacentPositions = GetAdjacentTileCoordinates(epicentre);
  adjacentPositions.push_back(epicentre);
  for (Position pos : adjacentPositions) {
    _board[pos.y][pos.x].SchrodingerTile();
  }
}
void Board::UnSchrodingerTiles(Position epicentre) {
  std::vector<Position> adjacentPositions = GetAdjacentTileCoordinates(epicentre);
  for (Position pos : adjacentPositions) {
    _board[pos.y][pos.x].UnSchrodingerTile();
  }
}

int Board::OpenTileGroup(Position epicentre) {
  std::vector<Position> adjacentPositions = GetAdjacentTileCoordinates(epicentre);
  Tile epicentreTile = _board[epicentre.y][epicentre.x];
  if (!epicentreTile.GetIsOpen()) {   return 0;   }
  int adjacentFlagCount = 0;
  for (Position pos : adjacentPositions) {
    if (_board[pos.y][pos.x].GetIsFlagged()) {   adjacentFlagCount++;   }
  }
  if (adjacentFlagCount != epicentreTile.GetInformation().adjacentMineCount) {   return 0;   }
  int tileResult = 0;
  for (int index = 0; index < adjacentPositions.size(); index++) {
    if (_board[adjacentPositions[index].y][adjacentPositions[index].x].GetIsOpen()) {
      adjacentPositions.erase(adjacentPositions.begin() + index);
    }
  }  
  do {
    Position pos = adjacentPositions.at(0);
    if (_board.at(pos.y).at(pos.x).GetIsOpen() || _board.at(pos.y).at(pos.x).GetIsFlagged()) {   adjacentPositions.erase(adjacentPositions.begin());   continue;   }
    tileResult = _board.at(pos.y).at(pos.x).OpenTile();
    if (tileResult == 1) {   return 1;   }
    if (tileResult == 2) {
      std::vector<Position> positions = GetAdjacentTileCoordinates(pos);
      adjacentPositions.insert(adjacentPositions.end(), positions.begin(), positions.end());
    }
  } while (adjacentPositions.size() > 0);
  return 0;
}

int Board::OpenTile(Position tilePosition) {
  int tileResult = _board[tilePosition.y][tilePosition.x].OpenTile();
  if (tileResult == 2) {   OpenTileGroup(tilePosition);   }
  return tileResult;
}

void Board::OpenAllMines() {
  for (int rowIndex = 0; rowIndex < _board.size(); rowIndex++) {
    for (int tileIndex = 0; tileIndex < _board.at(rowIndex).size(); tileIndex++) {
      Tile *tile = &(_board.at(rowIndex).at(tileIndex));
      if (tile->GetIsMine()) {   tile->OpenTile();   }
    }
  }
}

Board::Board(BoardData boardData) : _boardData(boardData) {
  Board::CreateNewBoard(boardData);
}
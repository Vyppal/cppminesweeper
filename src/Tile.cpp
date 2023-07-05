#include "Tile.h"
#include <map>
#include <iostream>

Tile::Tile(int xPos, int yPos) : _xPos(xPos), _yPos(yPos) {};

bool Tile::GetIsFlagged() {   return (_tileState == TileState::kFlagged);   }
bool Tile::GetIsOpen() {   return (_tileState == TileState::kActive);   }
bool Tile::GetIsMine() {   return _tileInformation.isMine == IsAMine::kMine;   }

int Tile::OpenTile() {
  // if (_tileState != TileState::kInactive && _tileState != TileState::kSchrodinger) {   return 0;   }
  if (_tileState == TileState::kInactive) {   std::cout << "i";   }
  else if (_tileState == TileState::kFlagged) {   std::cout << "f";   }
  else if (_tileState == TileState::kSchrodinger) {   std::cout << "s";   }
  else if (_tileState == TileState::kActive) {   std::cout << "a";   }
  if (GetIsMine()) {   return 1;   }
  std::cout << "w";
  _tileState = kActive;
  return 0;

}

void Tile::SwitchFlagTileState() {
  switch (_tileState) {
    case TileState::kInactive:
      _tileState = TileState::kFlagged;
     break;
    case TileState::kFlagged:
      _tileState = TileState::kInactive;
     break;
    default:
     break;
  }
}
void Tile::SchrodingerTile() {
  if (_tileState != TileState::kInactive) {   return;   }
  _tileState = TileState::kSchrodinger;
}
void Tile::UnSchrodingerTile() {
  if (_tileState != TileState::kSchrodinger) {   return;   }
  _tileState = TileState::kInactive;
}

void Tile::SetMine() {
  _tileInformation.isMine = kMine;
}
void Tile::AddAdjacentMine() {
  _tileInformation.adjacentMineCount = _tileInformation.adjacentMineCount + 1;
}
TileInformation Tile::GetInformation() {
  return _tileInformation;
}

int Tile::GetXPos() {   return _xPos;   }
int Tile::GetYPos() {   return _yPos;   }

void Tile::FinalizeTile() {
  std::string imagePath;
  std::map<int, std::string> Image;

  Image[0] = "zero.png";
  Image[1] = "one.png";
  Image[2] = "two.png";
  Image[3] = "three.png";
  Image[4] = "four.png";
  Image[5] = "five.png";
  Image[6] = "six.png";
  Image[7] = "seven.png";
  Image[8] = "eight.png";
  
  if (_tileState == TileState::kInactive) {   imagePath = "inactive.png";   }
  else if (_tileState == TileState::kFlagged) {   imagePath = "flag.png";   }
  else if (_tileState == TileState::kSchrodinger) {   imagePath = "zero.png";   }
  else if (GetIsMine()) {   imagePath = "mine.png";   }
  else {   imagePath = Image[_tileInformation.adjacentMineCount];   }
  _tileInformation.image = imagePath;
}

std::string Tile::GetSprite() {   return _tileInformation.image;   }

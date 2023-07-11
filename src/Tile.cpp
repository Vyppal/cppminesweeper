#include "Tile.h"

Tile::Tile(int xPos, int yPos) : _xPos(xPos), _yPos(yPos) {
  imageMap[0] = "zero.png";
  imageMap[1] = "one.png";
  imageMap[2] = "two.png";
  imageMap[3] = "three.png";
  imageMap[4] = "four.png";
  imageMap[5] = "five.png";
  imageMap[6] = "six.png";
  imageMap[7] = "seven.png";
  imageMap[8] = "eight.png";
  UpdateSetSprite();
};
 
bool Tile::GetIsFlagged() {   return (_tileState == TileState::kFlagged);   }
bool Tile::GetIsOpen() {   return (_tileState == TileState::kActive);   }
bool Tile::GetIsMine() {   return _tileInformation.isMine == IsAMine::kMine;   }

int Tile::OpenTile() {
  if (_tileState != TileState::kInactive && _tileState != TileState::kSchrodinger) {   return 0;   }
  _tileState = TileState::kActive;
  UpdateSetSprite();
  if (GetIsMine()) {   return 1;   }
  if (_tileInformation.adjacentMineCount == 0) {   return 2;   }
  return 0;

}

int Tile::SwitchFlagTileState() {
  switch (_tileState) {
    case TileState::kInactive:
      _tileState = TileState::kFlagged;
      UpdateSetSprite();
     return -1;
    case TileState::kFlagged:
      _tileState = TileState::kInactive;
      UpdateSetSprite();
     return 1;
    default:
     return 0;
  }
}
void Tile::SchrodingerTile() {
  if (_tileState != TileState::kInactive) {   return;   }
  _tileState = TileState::kSchrodinger;
  UpdateSetSprite();
}
void Tile::UnSchrodingerTile() {
  if (_tileState != TileState::kSchrodinger) {   return;   }
  _tileState = TileState::kInactive;
  UpdateSetSprite();
}

void Tile::SetMine() {
  _tileInformation.isMine = kMine;
}
void Tile::SetNotMine() {
  _tileInformation.isMine = kNonMine;
}
void Tile::AddAdjacentMine() {
  _tileInformation.adjacentMineCount = _tileInformation.adjacentMineCount + 1;
}
void Tile::RemoveAdjacentMine() {
  _tileInformation.adjacentMineCount = _tileInformation.adjacentMineCount - 1;
}
TileInformation Tile::GetInformation() {
  return _tileInformation;
}

int Tile::GetXPos() {   return _xPos;   }
int Tile::GetYPos() {   return _yPos;   }

void Tile::UpdateSetSprite() {
  std::string imagePath;
 
  if (_tileState == TileState::kInactive) {   imagePath = "inactive.png";   }
  else if (_tileState == TileState::kFlagged) {   imagePath = "flag.png";   }
  else if (_tileState == TileState::kSchrodinger) {   imagePath = "zero.png";   }
  else if (GetIsMine()) {   imagePath = "mine.png";   }
  else {   imagePath = imageMap[_tileInformation.adjacentMineCount];   }
  _tileInformation.image = texturePath + imagePath;
}

std::string Tile::GetSprite() {   return _tileInformation.image;   }

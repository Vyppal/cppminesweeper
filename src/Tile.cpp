#include "Tile.h"
#include <map>

Tile::Tile(int xPos, int yPos, GameHandler *gameHandler) : _xPos(xPos), _yPos(yPos), _gameHandler(gameHandler) {};

bool Tile::GetIsFlagged() {   return (_tileState == TileState::kFlagged);   }
bool Tile::GetIsOpen() {   return (_tileState == TileState::kActive);   }
bool Tile::GetIsMine() {   return _tileInformation.isMine == IsAMine::kMine;   }

void Tile::OpenTile() {
  if (_tileState != TileState::kInactive) {   return;   }
  if (GetIsMine()) {
    _gameHandler->SendActiveMineRequest();
    return;
  }
  _tileState = kActive;
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

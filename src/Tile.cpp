#include "Tile.h"

Tile::Tile(int xPos, int yPos, GameHandler &gameHandler) : _xPos(xPos), _yPos(yPos), _gameHandler(&gameHandler) {};

bool Tile::GetIsFlagged() {   return (_tileState == TileState::kFlagged);   }
bool Tile::GetIsOpen() {   return (_tileState == TileState::kActive);   }
bool Tile::GetIsMine() {   return _tileInformation.isMine;   }

void Tile::OpenTile() {
  if (_tileState != TileState::kInactive) {   return;   }
  if (_tileInformation.isMine) {
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
  _tileState = TileState::kSchrodingerState;
}

#include "Tile.h"

Tile::Tile(int xPos, int yPos) : _xPos(xPos), _yPos(yPos) {};

bool Tile::GetIsFlagged() {   return (_tileState == TileState::kFlagged);   }
bool Tile::GetIsOpen() {   return (_tileState == TileState::kActive);   }
bool Tile::GetIsMine() {   return _tileInformation.isMine;   }

void Tile::OpenTile() {
  if (!Tile::GetIsFlagged() && !Tile::GetIsOpen()) {
    
  }
}
void Tile::SwitchFlagTileState() {}
void Tile::SchrodingerTile() {}

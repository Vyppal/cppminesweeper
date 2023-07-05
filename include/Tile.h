#pragma once

#include <string>

enum IsAMine {
  kMine,
  kNonMine
};

enum TileState {
  /** The starting state of a tile (closed. unflagged) */
  kInactive,
  /** The opened state of a tile */
  kActive,
  /** The state of a tile when adjacent to a tile when the user is holding middle mouse button */
  kSchrodinger,
  /** The state of a flagged tile */
  kFlagged
};

struct TileInformation {
  int adjacentMineCount = 0;
  IsAMine isMine = IsAMine::kNonMine;
  std::string image = "inactive.png";
};

class Tile {
 public:
  Tile(int xPos, int yPos);
  
  // Check if the tile is flagged
  bool GetIsFlagged();
  // Check if the tile is opened
  bool GetIsOpen();
  // Check if the tile is a mine
  bool GetIsMine();

  int GetXPos();
  int GetYPos();

  // Opens the tile if it's not open, nor flagged. Returns 0 if not mine, 1 if is mine
  int OpenTile();
  // Sets the tile to flagged if it is inactive, and inactive if it is flagged
  void SwitchFlagTileState();
  // "Highlights" the current tile
  void SchrodingerTile();

  void SetMine();
  void AddAdjacentMine();

  // Gets the tile\s current state
  TileState GetTileState();
  TileInformation GetInformation();

  void FinalizeTile();
  std::string GetSprite();

 private:
  int _xPos, _yPos;
  TileState _tileState = TileState::kInactive;
  TileInformation _tileInformation;
};
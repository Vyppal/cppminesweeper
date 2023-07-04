#pragma once

enum TileState {
  /** The starting state of a tile (closed. unflagged) */
  kInactive,
  /** The opened state of a tile */
  kActive,
  /** The state of a tile when adjacent to a tile when the user is holding middle mouse button */
  kSchrodingerState,
  /** The state of a flagged tile */
  kFlagged
};

struct TileInformation {
  int adjacentMineCount;
  bool isMine;
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

  // Opens the tile if it's not open, nor flagged
  void OpenTile();
  // Sets the tile to flagged if it is inactive, and inactive if it is flagged
  void SwitchFlagTileState();
  // "Highlights" the current tile
  void SchrodingerTile();

  // Gets the tile\s current state
  TileState GetTileState();


 private:
  int _xPos, _yPos;
  TileState _tileState;
  TileInformation _tileInformation;
};
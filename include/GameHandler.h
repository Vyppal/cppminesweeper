#pragma once

struct GameConfig {
  int tileSize = 0;
};

class GameHandler {
 public:
  GameHandler(GameConfig _gameConfig);
  
  void SendActiveMineRequest();
  GameConfig GetConfig();

 private:
  bool _isGameOver = false;
  bool _isMineActive = false;
  GameConfig _gameConfig;
};
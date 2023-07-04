#pragma once

class GameHandler {
 public:
  GameHandler();
  
  void SendActiveMineRequest();

 private:
  bool _isGameOver = false;
  bool _isMineActive = false;

};
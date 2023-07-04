#include "GameHandler.h"

GameHandler::GameHandler(GameConfig gameConfig) : _gameConfig(gameConfig) {};

void GameHandler::SendActiveMineRequest() {   _isMineActive = true;   }

GameConfig GameHandler::GetConfig() {   return _gameConfig;   }


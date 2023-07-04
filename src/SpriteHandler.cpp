// #include "SpriteHandler.h"
// #include "GameHandler.h"

// #include <string>
// // #include <iostream>

// SpriteHandler::SpriteHandler(SDL_Window *window, GameHandler *gameHandler) : _window(window), _gameHandler(gameHandler) {}

// // std::string SpriteHandler::GetSprite(Tile *tile) {
// //   TileInformation tileInfo = tile->GetInformation();
// //   std::string imagePath = "";
// //   /* if (!tile->GetIsOpen()) {
// //     imagePath += "inactive.png";
// //   }
// //   else */if (tileInfo.isMine) {
// //     imagePath += "mine.png";
// //   }
// //   else {
// //     switch (tileInfo.adjacentMineCount) {
// //       case 0:
// //         imagePath += "zero.png";
// //        break;
// //       case 1:
// //         imagePath += "one.png";
// //        break;
// //       case 2:
// //         imagePath += "two.png";
// //        break;
// //       case 3:
// //         imagePath += "three.png";
// //        break;
// //       case 4:
// //         imagePath += "four.png";
// //        break;
// //       case 5:
// //         imagePath += "five.png";
// //        break;
// //       case 6:
// //         imagePath += "six.png";
// //        break;
// //       case 7:
// //         imagePath += "seven.png";
// //        break;
// //       case 8:
// //         imagePath += "eight.png";
// //        break;
// //       default:
// //         imagePath += "zero.png";
// //        break;
// //     }
// //   }
// //   return imagePath;
// // }

// // void SpriteHandler::DrawSprite(Tile *tile) {
// //   int tileSize = _gameHandler->GetConfig().tileSize;
// //   SDL_Rect _tileRect{tile->GetXPos() * tileSize, tile->GetYPos() * tileSize, tileSize, tileSize};
// //   SDL_Rect _tileRect{1 * 32, 1 * 32, 32, 32};
  
// //   std::string imagePath = GetSprite(tile);
// //   SDL_Surface *imageSurface = IMG_Load(("res/textures/" + imagePath).c_str());
// //   SDL_Surface *imageSurface = IMG_Load("res/textures/inactive.png");
  
// //   if (imageSurface == NULL) {   std::cout << "SDL could not load image! SDL Error: " << SDL_GetError( ) << std::endl;   return;   }
// //   int blitResult = SDL_BlitScaled(imageSurface, NULL, windowSurface, &_tileRect);
// //   if (blitResult < 0) {   std::cout << "blit failed" << std::endl;   }
// // }
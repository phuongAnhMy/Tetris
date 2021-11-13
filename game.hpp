#ifndef GAME_HPP_
#define GAME_HPP_

#include <SDL.h>
#include "well.hpp"
#include "tetromino.hpp"
#include <iostream>
#include "SDL_ttf.h"

class Game
{
public:
  Game();
  ~Game();
  bool tick();
  void RenderMenu();
  void DeRenderMenu();
  bool GameOutline();
private:

  SDL_Window *window_ = NULL;
  SDL_Renderer *renderer_ = NULL;
  TTF_Font* font1_ = NULL;
  SDL_Surface* surface1_ = NULL;
  SDL_Texture* texture1_ = NULL;

  TTF_Font *font2_ = NULL;
  SDL_Surface* surface2_ = NULL;
  SDL_Texture* texture2_ = NULL;

  Well well_;
  Tetromino tetromino_ = Tetromino(static_cast<Tetromino::Type>(rand() % 7));
  uint32_t moveTime_ = SDL_GetTicks();
  void check(const Tetromino &);
};

#endif //GAME_HPP_

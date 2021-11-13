#include "game.hpp"
#include <iostream>
#include "tetromino.hpp"
#include "CommonFunc.hpp"
#include "SDL_ttf.h"
#include <string>

using namespace std;

Game::Game()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        cout << "SDL_Init(SDL_INIT_VIDEO)" << SDL_GetError();
    if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
	}

    window_ = SDL_CreateWindow( "TETRIS", SDL_WINDOWPOS_UNDEFINED
                                        , SDL_WINDOWPOS_UNDEFINED
                                        , window_width, window_height
                                        , SDL_WINDOW_OPENGL);

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);


    if (window_ == NULL) {
        cout << "Could not create window: %s\n" <<  SDL_GetError();
    }
    if (renderer_ == NULL){
        cout << "Could not create renderer: %s\n" << SDL_GetError();
    }
}

void Game::RenderMenu()
{
    // RenderScore
    string score = to_string(well_.score);
    font1_ = TTF_OpenFont("bandit.ttf", 30);
    SDL_Color green = {133, 247, 56 };
    string text1 = "Score " + score;

    surface1_ = TTF_RenderText_Solid(font1_, text1.c_str(), green);
    texture1_ = SDL_CreateTextureFromSurface(renderer_, surface1_);
    SDL_FreeSurface(surface1_);

	SDL_Rect srcRest1;
	SDL_Rect desRect1;
	TTF_SizeText(font1_, text1.c_str(), &srcRest1.w, &srcRest1.h);

	srcRest1.x = 0;
	srcRest1.y = 0;

	desRect1.x = window_width - game_width / 2 - 20 ;
	desRect1.y = 180;

	desRect1.w = srcRest1.w;
	desRect1.h = srcRest1.h;

	SDL_RenderCopy(renderer_, texture1_, &srcRest1, &desRect1);
	// Render Tetris

	font2_ = TTF_OpenFont("bandit.ttf", 50);
	SDL_Color blue{84, 142, 234};
	string text2 = "TETRIS";

	surface2_ = TTF_RenderText_Solid(font2_, text2.c_str(), blue);
	texture2_ = SDL_CreateTextureFromSurface(renderer_, surface2_);
    SDL_FreeSurface(surface2_);

    SDL_Rect srcRest2;
	SDL_Rect desRect2;
	TTF_SizeText(font2_, text2.c_str(), &srcRest2.w, &srcRest2.h);

	srcRest2.x = 0;
	srcRest2.y = 0;

	desRect2.x = window_width - game_width / 2 - 30 ;
	desRect2.y = 50;

	desRect2.w = srcRest2.w;
	desRect2.h = srcRest2.h;

    SDL_RenderCopy(renderer_, texture2_, &srcRest2, &desRect2);

}
void Game::DeRenderMenu()
{
   SDL_DestroyTexture(texture1_);
   SDL_DestroyTexture(texture2_);
   TTF_CloseFont(font1_);
   TTF_CloseFont(font2_);
}
bool Game::GameOutline() // MENU OUTLINE
{
    SDL_Rect square1 {game_width, 0, outline_width, outline_height};
    SDL_SetRenderDrawColor(renderer_, 252, 169, 68, 0 );
    SDL_RenderFillRect(renderer_, &square1);

    SDL_Rect square2 {game_width + 5, 0, outline_width - 20, outline_height };
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0 );
    SDL_RenderFillRect(renderer_, &square2);

    SDL_Rect square3 {game_width, 150, game_width, 5};
    SDL_SetRenderDrawColor(renderer_, 252, 169, 68, 0);
    SDL_RenderFillRect(renderer_, &square3);

    return true;
}
Game::~Game()
{
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  TTF_Quit();
  SDL_Quit();
}

bool Game::tick()
{

  SDL_Event e;
  while(SDL_PollEvent(&e))
  {
    switch (e.type)
    {
    case SDL_KEYDOWN:
      {
        switch (e.key.keysym.sym)
        {
        case SDLK_DOWN:
          {
            Tetromino t = tetromino_;
            t.moves(0, 1);
            if (!well_.isCollision(t)){
              tetromino_ = t;
            }
          }
          break;
        case SDLK_RIGHT:
          {
            Tetromino t = tetromino_;
            t.moves(1, 0);
            if (!well_.isCollision(t))
              tetromino_ = t;
          }
          break;
        case SDLK_LEFT:
          {
            Tetromino t = tetromino_;
            t.moves(-1, 0);
            if (!well_.isCollision(t))
              tetromino_ = t;
          }
          break;
        case SDLK_UP:
          {
            Tetromino t = tetromino_;
            t.rotates();
            if (!well_.isCollision(t))
              tetromino_ = t;
          }
          break;
        }
      }
      break;

    case SDL_QUIT:
      return false;
    }
  }

  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);
  SDL_RenderClear(renderer_);

  well_.draw(renderer_);
  tetromino_.draw(renderer_);

  if (SDL_GetTicks() > moveTime_ )
  {
    moveTime_ += 300;
    Tetromino t = tetromino_;
    t.moves(0, 1);
    check(t);
  }
  DeRenderMenu();
  GameOutline();
  RenderMenu();

  SDL_RenderPresent(renderer_);
  return true;
};

void Game::check(const Tetromino &t)
{

  if (well_.isCollision(t))
  {
    well_.unite(tetromino_);

    tetromino_ = Tetromino{static_cast<Tetromino::Type>(rand() % 7)};
    if (well_.isCollision(tetromino_))
    {
      well_ = Well();
    }
  }
  else
  {
    tetromino_ = t;
  }
}

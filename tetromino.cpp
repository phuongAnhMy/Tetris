#include "tetromino.hpp"
#include "CommonFunc.hpp"
#include <iostream>

using namespace std;

Tetromino::Tetromino(Type type )
{
    type_ = type; // loai tetromino
    x_ = 10 / 2 - 4 / 2; // diem bat dau
    y_ = 0; //
    angle_ = 0; // hinh ban dau
}

void Tetromino::draw(SDL_Renderer *renderer)
{
  switch (type_)
  {
  case I:
    SDL_SetRenderDrawColor(renderer, 224, 35, 35, 0);
    break;
  case J:
    SDL_SetRenderDrawColor(renderer, 111, 114, 100, 0);
    break;
  case L:
    SDL_SetRenderDrawColor(renderer, 222, 114, 224, 0);
    break;
  case O:
    SDL_SetRenderDrawColor(renderer, 9, 128, 247, 0);
    break;
  case S:
    SDL_SetRenderDrawColor(renderer, 244, 119, 29, 0);
    break;
  case T:
    SDL_SetRenderDrawColor(renderer, 209, 137, 79, 0);
    break;
  case Z:
    SDL_SetRenderDrawColor(renderer, 6, 232, 74, 0);
    break;
  }

  for (int x = 0; x < 4; ++x)
    for (int y = 0; y < 4; ++y)
      if (isBlock(x, y))
      {
        SDL_Rect rect{(x + x_) * game_width / 10 + 1, (y + y_) * game_width / 10 + 1, game_width / 10 - 2, game_width / 10 - 2};
        SDL_RenderFillRect(renderer, &rect);
      }
}

void Tetromino::moves(int dx, int dy)
{
  x_ += dx;
  y_ += dy;
}
void Tetromino::rotates()
{
  angle_ += 1;
  angle_ %= 4;
}

bool Tetromino::isBlock(int x, int y) const
{
   const char *Shapes[7][4] = {
    {// I
      " *  "
      " *  "
      " *  "
      " *  ",

      "    "
      "****"
      "    "
      "    ",

      " *  "
      " *  "
      " *  "
      " *  ",

      "    "
      "****"
      "    "
      "    ",
    },
    {// J
      "  * "
      "  * "
      " ** "
      "    ",

      "    "
      "*   "
      "*** "
      "    ",
      " ** "
      " *  "
      " *  "
      "    ",
      "    "
      "    "
      "*** "
      "  * ",
    },
    {// L
      " *  "
      " *  "
      " ** "
      "    ",

      "    "
      "*** "
      "*   "
      "    ",

      " ** "
      "  * "
      "  * "
      "    ",
      "  * "
      "*** "
      "    "
      "    ",
    },
    {
      "    "
      " ** "
      " ** "
      "    ",
      "    "
      " ** "
      " ** "
      "    ",
      "    "
      " ** "
      " ** "
      "    ",

      "    "
      " ** "
      " ** "
      "    ",
    },
    {
      "  * "
      " ** "
      " *  "
      "    ",
      "    "
      "**  "
      " ** "
      "    ",
      "  * "
      " ** "
      " *  "
      "    ",
      "    "
      "**  "
      " ** "
      "    ",
    },
    {
      " *  "
      " ** "
      " *  "
      "    ",
      "    "
      "*** "
      " *  "
      "    ",

      "    "
      " *  "
      "**  "
      " *  ",
      "    "
      " *  "
      "*** "
      "    ",
    },
    {
      " *  "
      " ** "
      "  * "
      "    ",

      "    "
      " ** "
      "**  "
      "    ",

      " *  "
      " ** "
      "  * "
      "    ",

      "    "
      " ** "
      "**  "
      "    ",
    },
  };

  return Shapes[type_][angle_][x + y * 4] == '*';
}
int Tetromino::x() const
{
  return x_;
}
int Tetromino::y() const
{
  return y_;
}

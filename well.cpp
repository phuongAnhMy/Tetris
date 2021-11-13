#include "well.hpp"
#include "game.hpp"
#include "CommonFunc.hpp"
#include <iostream>

using namespace std;

Well::Well()
{// tao 1 ma tran bool 10x20 la 0
    for (int y = 0; y < Height; y++)
        for (int x = 0; x < Width; x++)
            data[x][y] = false;

}

void Well::draw(SDL_Renderer *renderer)
{

  for (int x = 0; x < Width; ++x)
    for (int y = 0; y < Height; ++y)
    {

        SDL_SetRenderDrawColor(renderer, 55, 180, 242, 0);

      if (data[x][y])
      {
        SDL_Rect rect{ x * game_width / Width + 1, y * game_width / Width + 1,
                        game_width / Width - 2, game_width / Width - 2};
        SDL_RenderFillRect(renderer, &rect);
      }
      else{
         SDL_SetRenderDrawColor(renderer, 237, 233, 232, 0);
        SDL_RenderDrawPoint(renderer, x * game_width / Width ,
                            y * game_width / 10 );
        }
    }
}

bool Well::isCollision(const Tetromino &t) const
{
  for (int x = 0; x < 4; ++x)
    for (int y = 0; y < 4; ++y)
      if (t.isBlock(x, y))
// x represent the position of blocks in y row
      {
        int wx = t.x() + x;
        int wy = t.y() + y;
        if (wx < 0 || wx >= Width || wy < 0 || wy >= Height)
          return true;
        if (data[wx][wy])
          return true;
      }
  return false;
}

void Well::unite(const Tetromino &t)
{
  for (int x = 0; x < 4; ++x)
    for (int y = 0; y < 4; ++y)
      if (t.isBlock(x, y))
        data[t.x() + x][t.y() + y] = true;
/* This lines of code will check on each square_width (= 10)
 if this is full-square row then the row above it will become the row below
 .Then y += 1 will be used to check again
            |
            |
            V
*/
  bool solid = false;
  int counter_row = 0;

  for (int y = Height - 1; y >= 0; --y)
  {
      if (solid == true)
      {
          y += 1;
          counter_row++;
      }
      solid = true;
    for (int x = 0; x < Width; ++x)
      if (!data[x][y])
      {
        solid = false;
        break;
      }
    if (solid)
    {
      for (int yy = y - 1 ; yy >= 0; --yy)
        for (int x = 0; x < Width; ++x)
          data[x][yy + 1] = data[x][yy];
    }
  }
    score += 100 * counter_row * counter_row ;
}

#ifndef WELL_HPP_H
#define WELL_HPP_H

#include "tetromino.hpp"
#include <SDL.h>

class Well
{
public:
  Well();
  void draw(SDL_Renderer *);
  enum { Width = 10, Height = 20 };
  bool isCollision(const Tetromino &t) const;
  void unite(const Tetromino &);
  int score = 0;
private:
  bool data[Width][Height]; //* data[x][y]


};

#endif // WELL_HPP_H

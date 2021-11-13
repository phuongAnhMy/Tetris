#ifndef TETROMINO_HPP_
#define TETROMINO_HPP_

#include <SDL.h>

class Tetromino
{
public:
  enum Type { I = 0, J, L, O, S, T, Z };
  Tetromino(Type);
  void draw(SDL_Renderer *);
  void moves(int dx, int dy);
  void rotates();
  bool isBlock(int x, int y) const;
  int x() const;
  int y() const;

private:
  int x_;
  int y_;
  int angle_;
   Type type_;

 // 0 - 0deg, 1 - 90deg, 2 - 180deg, 3 - 270deg
};
#endif // TETROMINO_HPP_

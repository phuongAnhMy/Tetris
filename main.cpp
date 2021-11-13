#include "game.hpp"
#include <iostream>
#include <time.h>

int main(int argc, char *argv[])
{
  srand(time(0));
  Game game;
  while (game.tick());

  return 0;
}

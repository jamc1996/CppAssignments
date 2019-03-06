#include <iostream>
#include <unistd.h>

//#include "player.h"
#include "Board.h"


int main(int argc, char *argv[])
{
  int c;
  char red_player = 0; char yellow_player = 0;
  while ((c = getopt( argc, argv, "ry")) != -1)
  {
    switch(c)
    {
    case 'r':
      red_player = 1;
    case 'y':
      yellow_player = 1;
    case '?':
      break;
    }
  }

  Board board(6,7);
  board.make_move(true,  3);
  board.make_move(false,  3);
  board.make_move(true,  1);

  board.print();

  std::cout << sizeof(bool) << std::endl;
  return 0;
}

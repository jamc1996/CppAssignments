#include <iostream>
#include <unistd.h>

#include "player.h"
#include "Board.h"


int main(int argc, char *argv[])
{
  int c,i;
  bool red_player = false;
  bool yellow_player = false;
  while ((c = getopt( argc, argv, "ry")) != -1)
  {
    switch(c)
    {
    case 'r':
      red_player = true;
      break;
    case 'y':
      yellow_player = true;
      break;
    case '?':
      break;
    }
  }
  int n = 6;
  int m = 7;
  Board board(n,m);
  player* r = NULL;
  player* y = NULL;

  if (!red_player)
  {
    r = new human_player(true);
  }
  else
  {
    r = new machine_player(true, n, m);
  }

  if (!yellow_player)
  {
    y = new human_player(false);
  }
  else
  {
    y = new machine_player(false, n, m);

  }

  for ( i = (n*m)/2; i--;)
  {
    std::cout << board.valids[0] << std::endl;
    r->move_choice(&board);
    std::cout << "\033[31m" << "Red plays " << board.last_move << "\033[0m" <<std::endl;
    board.red_win = board.check_win(board.red_entry);
    if (board.red_win)
    {
      break;
    }
    std::cout << board.valids[0] << std::endl;
    y->move_choice(&board);
    std::cout << "\033[33m" << "Yellow plays " << board.last_move << "\033[0m" << std::endl;
    board.yellow_win = board.check_win(board.yellow_entry);
    if (board.yellow_win)
    {
      break;
    }
  }
  board.print();

  if (board.red_win) {
    std::cout << "\033[31m" << " RED PLAYER WINS!!! " << "\033[0m" << std::endl;
  }
  else if (board.yellow_win)
  {
    std::cout << "\033[33m" << " YELLOW PLAYER WINS!!! " << "\033[0m" << std::endl;
  }
  else
  {
    std::cout << "DRAW!!!" << std::endl;
  }
  // board.make_move(true,  3);
  // board.make_move(false,  3);
  // board.make_move(true,  1);


  return 0;
}

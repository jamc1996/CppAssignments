#include <iostream>
#include <unistd.h>

#include "player.h"
#include "board.h"
#include "game.h"

/*    main.cc -- program to run Connect4 game using player, board and game files.
 *
 *    Author: John Cormican
 *
 *    Purpouse: To play Connect4 on the terminal.
 *
 *    Usage: Compile with the provided make file and run with optional args.
 */

int main(int argc, char *argv[])
/*  Function that runs the connect 4 game by calling
 *  board, player and game classes.
 */
{

  // Command line arguments to choose machine or human players and search depth
  int c;
  bool red_player = false;
  bool yellow_player = false;
  int d = 11;
  while ((c = getopt( argc, argv, "ryd:")) != -1)
  {
    switch(c)
    {
    case 'r':
      red_player = true;
      break;
    case 'y':
      yellow_player = true;
      break;
    case 'd':
      d = atoi(optarg);
      break;
    case '?':
      break;
    }
  }

  // Board dimensions set and abstract player class declared
  int n = 6;
  int m = 7;
  Board board(n,m);
  Player* r = NULL;
  Player* y = NULL;

  // human/machine player constructed based on command line args.
  if (!red_player)
  {
    r = new HumanPlayer(true);
  }
  else
  {
    r = new MachinePlayer(true, n, m, d);
  }
  if (!yellow_player)
  {
    y = new HumanPlayer(false);
  }
  else
  {
    y = new MachinePlayer(false, n, m, d);
  }

  // Game played:
  Game game(r, y, &board);
  game.play();


  delete r;
  delete y;


  return 0;
}

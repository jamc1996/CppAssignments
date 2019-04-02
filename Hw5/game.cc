#include "game.h"

/*    game.cc -- functions for Game class in a Connect4 game.
 *
 *    Author: John Cormican
 *
 *    Purpouse: To facilitate a game between two human/machine players
 *
 *    Usage:  play() called from main function to manage game.
 */

Game::Game(Player* red, Player* yellow, Board* b) : red_player(red), yellow_player(yellow), board(b)
/* Constructor for Game class. */
{
  std::cout << "Game Started! Red plays first!" << '\n';
}


void Game::play()
{
  // Timing included to check whether changes to algorithm made a difference.
  clock_t start, end;
  double time;
  int i;

  //Game runs:
  for ( i = (board->nrows*board->ncols)/2; i--;)
  {
    // Board printed for player:
    board->print();

    // Move played with timing
    start = clock();
    red_player->move_choice(board);
    end = clock();

    // Output move and time to terminal
    time = (double)(end-start)/CLOCKS_PER_SEC;
    std::cout << "Move time:" << time << '\n';
    std::cout << "\033[31m" << "Red plays " << board->last_move+1 << "\033[0m" <<std::endl;

    // Check if winning move has been played
    board->red_win = board->check_win(board->red_entry);
    if (board->red_win)
    {
      break;
    }

    // Board printed for player:
    board->print();

    // Move played with timing
    start = clock();
    yellow_player->move_choice(board);
    end = clock();

    // Output move and time to terminal
    time = (double)(end-start)/CLOCKS_PER_SEC;
    std::cout << "Move time:" << time << '\n';
    std::cout << "\033[33m" << "Yellow plays " << board->last_move+1 << "\033[0m" << std::endl;

    // Check if winning move played
    board->yellow_win = board->check_win(board->yellow_entry);
    if (board->yellow_win)
    {
      break;
    }
  }

  // With game over final position and result printed to screen.
  print_result();
}

void Game::print_result()
/* Function to print the result of the game. */
{
  board->print();
  if (board->red_win) {
    std::cout << "\033[31m" << " RED PLAYER WINS!!! " << "\033[0m" << std::endl;
  }
  else if (board->yellow_win)
  {
    std::cout << "\033[33m" << " YELLOW PLAYER WINS!!! " << "\033[0m" << std::endl;
  }
  else
  {
    std::cout << "DRAW!!!" << std::endl;
  }
}

Game::~Game()
{
  //Another unecessary destructor that I chose.
}

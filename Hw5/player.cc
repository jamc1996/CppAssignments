#include <iostream>

#include "player.h"

/*      player.cc -- program with Player classes for Connect4 games.
 *
 *      Author:     John Cormican
 *
 *      Purpouse:   To allow user to play against computer through terminal.
 *
 *      Usage:      Methods called from main.cc to simulate playing of Connect4.
 */



MachinePlayer::MachinePlayer(bool r,int n, int m, int d) : p1(r), depth(d), virtual_board(n,m)
/* Constructor for machine player class. Initializes values and prints message. */
{
  // Move ordering done to increase calculation speed:
  order.push_back(m/2);
  for (int i = 1; i <= m/2; i++)
  {
    order.push_back((m/2)-i);
    if (m%2 == 0 && i == m/2) {
      break;
    }
    order.push_back((m/2)+i);
  }
  std::cout << "Machine player ready!" << std::endl;
}


HumanPlayer::HumanPlayer(bool r) : p1(r)
/* Constructor for human player class. */
{
  if (p1) {
    std::cout << "Human playing red." <<std::endl;
  }
  else
  {
    std::cout << "Human playing yellow." <<std::endl;
  }
}



void HumanPlayer::move_choice(Board *board)
/*    Function takes human input, checks that it is valid and
 *    makes the corresponding move.  */
{

  // Input is error checked using bad_move flag.
  bool bad_move = true;
  int move;
  while (bad_move)
  {
    bad_move = false;
    std::cout << "Choose a column (1-7):" <<std::endl;
    std::cin >> move;

    // Check move in an integer:
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "player.cc: Invalid option, please enter an integer." << std::endl;
      bad_move = true;
      continue;
    }

    // Check move in valid range:
    if (move < 1 || move > 7 )
    {
      std::cout << "player.cc: Invalid option, please enter a value from 1-7." << std::endl;
      bad_move = true;
      continue;
    }
    move--;

    // Check column isn't full:
    if (board->valids[move]>=6)
    {
      std::cout << "player.cc: Invalid option, column is full." << std::endl;
      bad_move = true;
      continue;
    }
  }

  // Update last move for machine player opponent and makes move on game board.
  board->set_lastmove(move);
  board->make_move(p1,move);
}


void MachinePlayer::move_choice(Board *board)
/* Function for computer to choose its best option. */
{
  // Update the virtual board
  if (board->last_move!=-1) {
    MakeFakeMove(!p1,board->last_move);
  }
  // check_options() used to increase depth as available moves decreases.
  check_options();

  // Symmetry checked to cut double calculation
  bool symmetry = virtual_board.check_symmetry();

  // Variables for selecting best option
  double val;
  int candidate_move;
  int best_move = -1;
  double best_val = -400;
  std::vector<double> scores;
  for (int i = 0; i < board->ncols; i++)
  {
    scores.push_back(-400);
  }

  // Loop to evaluate moves
  for(int j = 0; j<board->ncols; j++)
  {
    candidate_move = order[j];
    if (symmetry && candidate_move>3)
    {
      continue;
    }
    if (virtual_board.valids[candidate_move] < virtual_board.nrows)
    {
      MakeFakeMove(p1,candidate_move);
      if (virtual_board.check_win(my_discs(p1)))
      {
        best_move = candidate_move;
        UnmakeFakeMove(p1,candidate_move);
        break;
      }
      val = -search(-380, 380, depth, !p1);
      // Usually evaluation function is run at end but it is quite costly so I
      // used it at original move if no wins were found.
      if (val == 0)
      {
        val = evaluation_function(&virtual_board,p1,candidate_move);
      }
      scores[candidate_move] = val;
      if (val>best_val)
      {
        best_val = val;
        best_move = candidate_move;
      }
      UnmakeFakeMove(p1,candidate_move);
    }
  }

  board->set_lastmove(best_move);
  virtual_board.make_move(p1,best_move);
  virtual_board.set_lastmove(best_move);
  check_options();
  board->make_move(p1,best_move);
}


double MachinePlayer::search( double alpha, double beta, int depth, bool re)
/* Recursive min max search with alpha-beta pruning */
{
  int k, j;
  double val = -300.0;
  bool symmetry = virtual_board.check_symmetry();
  if (depth == 0)
  {
    return 0.0;
  }

  // Search through all moves
  for(j = 0; j<virtual_board.ncols; j++)
  {
    k = order[j];
    if (symmetry && k>(virtual_board.ncols/2))
    {
      continue;
    }
    if (virtual_board.valids[k]< virtual_board.nrows)
    {
      MakeFakeMove(re,k);
      if (virtual_board.check_win(my_discs(re)))
      {
        UnmakeFakeMove(re,k);
        val = (double)(200+depth);
      }
      else
      {
        val = -search(-beta, -alpha, depth-1, !re);
        UnmakeFakeMove(re, k);
      }
      if (val > alpha)
      {
        alpha = val;
      }
      if (alpha >= beta)
      {
        return alpha;
      }
    }
  }

  // This check catches if board filled with no result
  if (fabs(val+300.0)<0.0001) {
    return 0.05;
  }

  return alpha;
}

void MachinePlayer::check_options()
/* Function to check how close to full a column is and increase depth near full */
{
  if (virtual_board.last_move != -1)
  {
    if (virtual_board.valids[virtual_board.last_move] > virtual_board.nrows - 2)
    {
      increase_depth(1);
    }
  }
}

double MachinePlayer::evaluation_function(Board *board, bool player_is_red, int candidate_move)
/* Function to find the establish the value of position to one player. */
{
  double x,y;
  if (player_is_red)
  {
    x = board->check_threats(board,board->red_entry,board->yellow_entry,false);
    y = board->check_threats(board,board->yellow_entry,board->red_entry,true);
  }
  else
  {
    x = board->check_threats(board,board->yellow_entry,board->red_entry,false);
    y = board->check_threats(board,board->red_entry,board->yellow_entry,true);
  }
  // Threats were less use on column 6 and so x is docked slightly.
  if (virtual_board.valids[candidate_move]==virtual_board.nrows)
  {
    x-=2.0;
  }
  return x - y;
}

void MachinePlayer::UnmakeFakeMove(bool re, int move)
/* Move for undoing fake move after line has been analyzed. */
{
  virtual_board.unmake_move(re,move);
}

void MachinePlayer::MakeFakeMove(bool re, int move)
/* Move for making fake move on virtual board. */
{
  virtual_board.make_move(re,move);
  virtual_board.set_lastmove(move);
}

bool** MachinePlayer::my_discs(bool p)
/* Function to return the discs of a player. */
{
  if (p) {
    return virtual_board.red_entry;
  }
  return virtual_board.yellow_entry;
}
void MachinePlayer::increase_depth(int i)
/* Function to increase the depth of search. */
{
  depth+=i;
}

//Destructors weren't necessary but seemed like good practise to keep them in.

Player::~Player()
{

}

MachinePlayer::~MachinePlayer()
{

}

HumanPlayer::~HumanPlayer()
{

}

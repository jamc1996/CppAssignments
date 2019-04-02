#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include <math.h>
#include <vector>
#include <limits>

/*      player.h -- header file for the Player classes.
 *
 *      Author:     John Cormican
 *
 */

class Player
/* Abstact class both HumanPlayer and */
{
public:
  virtual void move_choice(Board *board)=0;
  virtual ~Player();
};


class HumanPlayer : public Player
/* class with functions required to allow human to play with terminal input. */
{
private:
  bool p1;

public:
  HumanPlayer(bool red);
  virtual void move_choice(Board *board);
  ~HumanPlayer();
};

class MachinePlayer : public Player
{
private:
  bool p1;
  int depth;
  Board virtual_board;
  std::vector<int> order;

public:
  //Constructor
  MachinePlayer(bool red, int n, int m, int d);

  // Necessary function for good machine performance
  double evaluation_function(Board *board, bool player, int candidate_move);
  virtual void move_choice(Board *board);
  bool** my_discs(bool p);
  void check_options();
  void increase_depth(int i);
  double search(double alpha, double beta, int depth, bool re);
  void MakeFakeMove(bool re, int move);
  void UnmakeFakeMove(bool re, int move);


  ~MachinePlayer();

};

#endif

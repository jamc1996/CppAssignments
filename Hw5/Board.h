#ifndef BOARD_H
#define BOARD_H

#include <iostream>

/*      board.h -- header file for the Board class.
 *
 *      Author:     John Cormican
 *
 */

class Board
{
  //It was easiest to let other classes access everything in board.
  friend class Player;
  friend class MachinePlayer;
  friend class HumanPlayer;
  friend class Game;

private:
  // Board dimensions
  int nrows;
  int ncols;

  // Data stored in two different arrays of true/false values:
  bool* red_spots;
  bool* yellow_spots;
  bool** red_entry;
  bool** yellow_entry;

  bool red_win, yellow_win;
  int last_move;

  // Array of integers for where next move goes in each column
  int* valids;

public:
  // Constructor:
  Board(const int n, const int m);

  // Allow moves to be made and taken back (needed for search)
  void make_move(bool p, int i);
  void unmake_move(bool p, int i);

  // Different board features:
  void set_lastmove(int move);
  bool check_symmetry();
  bool check_win(bool** reds);

  // Used by evaluation function:
  double check_threats(Board* board, bool** mine, bool ** ops, bool to_play);

  // Board printing
  void print();

  ~Board();

};

#endif

#ifndef BOARD_H
#define BOARD_H

class Board
{
public:
  int nrows;
  int ncols;
  bool* red_spots;
  bool* yellow_spots;
  bool** red_entry;
  bool** yellow_entry;
  bool red_win, yellow_win;
  int* valids;
  int last_move;


  // Constructor:


  Board(const int n, const int m);

  void make_move(bool p, int i);
  void unmake_move(bool p, int i);
  void set_lastmove(int move);

  bool check_win(bool** reds);

  void print();

//  ~Board();

};

#endif

#include "Board.h"
#include <vector>
#include <list>

class player
{
public:
  //bool p1;
  //std::vector<bool> move_generator(Board board);

  virtual void move_choice(Board *board)=0;
  //virtual int search(Board board);

  //virtual int evaluation_function();
};


class human_player : public player
{
public:
  bool p1;
  human_player(bool red);
  virtual void move_choice(Board *board);

};

class machine_player : public player
{
public:
  bool p1;
  Board virtual_board;
  std::list<int> line;

  machine_player(bool red, int n, int m);

  virtual void move_choice(Board *board);

  bool** my_discs(bool p);

  float search(float alpha, float beta, int depth, bool re);

  void MakeFakeMove(bool re, int move, std::list<int> line);
  void UnmakeFakeMove(bool re, int move, std::list<int> line);


  //std::vector<bool> moves_generator(Board virtual_board);

};

#include <iostream>

#include "player.h"

machine_player::machine_player(bool r,int n, int m) : p1(r), virtual_board(n,m)
{
  std::cout << "Machine player ready!" << std::endl;
}


human_player::human_player(bool r) : p1(r)
{
  if (p1) {
    std::cout << "Human playing red." <<std::endl;
  }
  else
  {
    std::cout << "Human playing yellow." <<std::endl;
  }
}


void human_player::move_choice(Board *board)
{
  board->print();
  bool bad_move = true;
  int move;
  while (bad_move)
  {
    bad_move = false;
    std::cout << "Choose a column (1-7):" <<std::endl;
    std::cin >> move;
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "player.cc: Invalid option, please enter an integer." << std::endl;
      bad_move = true;
      continue;
    }

    if (move < 1 || move > 7 )
    {
      std::cout << "player.cc: Invalid option, please enter a value from 1-7." << std::endl;
      bad_move = true;
      continue;
    }
    move--;
    if (board->valids[move]==6)
    {
      std::cout << "player.cc: Invalid option, column is full." << std::endl;
      bad_move = true;
      continue;
    }
  }
  board->set_lastmove(move);
  board->make_move(p1,move);
}

void machine_player::move_choice(Board *board)
{
  int i, depth = 3;
  float val = -2;
  int best_move = 0;
  float best_val = -2.0;
  std::vector<bool> moves = moves_generator(virtual_board);
  std::vector<int> scores = {-2,-2,-2,-2,-2,-2,-2};
  if (board->last_move!=-1) {
    printf("Making last move\n" );
    MakeFakeMove(!p1,board->last_move,line);
  }
  virtual_board.print();

  std::cout << moves[4] << '\n';
  for(i = 0; i<7; i++)
  {
    if (moves[i])
    {
      MakeFakeMove(p1,i,line);
      if (virtual_board.check_win(my_discs(p1)))
      {
        best_move = i;
        UnmakeFakeMove(p1,i,line);
        break;
      }
      val = -search(1, -1, depth, !p1);
      printf("Move %d returns a value of %f\n",i,val );
      if (val>best_val)
      {
        best_val = val;
        best_move = i;
      }
      UnmakeFakeMove(p1,i,line);
    }
  }
  board->set_lastmove(best_move);
  virtual_board.make_move(p1,best_move);
  board->make_move(p1,best_move);
}


float machine_player::search( int alpha, int beta, int depth, bool re)
{
  std::cout << "re is " << re << '\n';
  if (depth == 0)
  {
    return 0.0;
  }
  int k;
  int val;
  std::vector<bool> moves = moves_generator(virtual_board);
  for(k = 0; k<7; k++)
  {
    std::cout << "Move" << k << " " << moves[k] << '\n';
    if (moves[k])
    {
      MakeFakeMove(re,k,line);
      if (virtual_board.check_win(my_discs(re)))
      {
        std::cout << "For " << re << " the winning position is" << '\n';
        virtual_board.print();
        UnmakeFakeMove(re,k,line);
        return 1.0/(float)(100-depth);
      }
      val = -search(-beta, -alpha, depth -1,!re);
      UnmakeFakeMove(re,k,line);
    }
  }
  return val;
}

void machine_player::UnmakeFakeMove(bool re, int move, std::list<int> line)
{
  std::cout << "Now reversing " << re << " at " << move << '\n';
  virtual_board.unmake_move(re,move);
}

void machine_player::MakeFakeMove(bool re, int move, std::list<int> line)
{
  std::cout << "Now playing " << re << " at " << move << '\n';
  virtual_board.make_move(re,move);
  line.push_front(move);
}

bool** machine_player::my_discs(bool p)
{
  if (p) {
    return virtual_board.red_entry;
  }
  return virtual_board.yellow_entry;
}


std::vector<bool> machine_player::moves_generator(Board virtual_board)
{
  std::vector<bool> moves = {true, true, true, true, true, true, true};
  for (int i = 0; i < 7; i++)
  {
    if (virtual_board.valids[i] == 6) {
      moves[i] = false;
    }
  }
  return moves;
}

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
    if (board->valids[move]>=6)
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
  int i, depth = 10;
  float val = -2;
  int best_move = -1;
  float best_val = -2.0;
  std::vector<float> scores = {-2.0,-2.0,-2.0,-2.0,-2.0,-2.0,-2.0};
  std::vector<int> order = {3,2,4,1,5,0,6};
  if (board->last_move!=-1) {
    MakeFakeMove(!p1,board->last_move,line);
  }
  virtual_board.print();
  for(int j = 0; j<7; j++)
  {
    i = order[j];
    if (virtual_board.valids[i] <= 5)
    {
      MakeFakeMove(p1,i,line);
      if (virtual_board.check_win(my_discs(p1)))
      {
        best_move = i;
        UnmakeFakeMove(p1,i,line);
        break;
      }
      val = -search(-1.9, 1.9, depth, !p1);
      scores[i] = val;
      if (val>best_val)
      {
        best_val = val;
        best_move = i;
      }
      UnmakeFakeMove(p1,i,line);
    }
  }
  for (int i = 0; i < 7; i++) {
    std::cout << "Score of move " << i << " = " << scores[i] << '\n';
  }
  board->set_lastmove(best_move);
  virtual_board.make_move(p1,best_move);
  board->make_move(p1,best_move);
}


float machine_player::search( float alpha, float beta, int depth, bool re)
{
  int k;
  float val = -1.5;
  bool no_moves = true;

  if (depth == 0)
  {
    return 0.0;
  }
  for(k = 0; k<7; k++)
  {
    if (virtual_board.valids[k]<=5)
    {
      no_moves = false;
      MakeFakeMove(re,k,line);
      if (virtual_board.check_win(my_discs(re)))
      {
        UnmakeFakeMove(re,k,line);
        val = 1.0/(float)(15-depth);
      }
      else
      {
        val = -search(-beta, -alpha, depth-1, !re);
        UnmakeFakeMove(re, k, line);
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
  if (no_moves) {
    return 0;
  }
  return alpha;
}

void machine_player::UnmakeFakeMove(bool re, int move, std::list<int> line)
{
  virtual_board.unmake_move(re,move);
}

void machine_player::MakeFakeMove(bool re, int move, std::list<int> line)
{
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

// std::vector<bool> machine_player::moves_generator(Board virtual_board)
// {
//   std::vector<bool> moves = {true, true, true, true, true, true, true};
//   for (int i = 0; i < 7; i++)
//   {
//     if (virtual_board.valids[i] >= 6) {
//       moves[i] = false;
//     }
//   }
//   return moves;
// }

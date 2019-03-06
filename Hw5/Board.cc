#include <iostream>

#include "Board.h"

Board::Board(int n, int m) : nrows(n), ncols(m), red_spots(new bool[n*m]), yellow_spots(new bool[n*m]), valids(new int[m]), red_entry(new bool*[m]), yellow_entry(new bool*[m]), red_win(false), yellow_win(false)
{
  for (int i = 0; i < 42; i++)
  {
    red_spots[i] = false;
    yellow_spots[i] = false;
  }

  for (int i = 0; i < 7; i++)
  {
    red_entry[i] = &red_spots[i*6];
    yellow_entry[i] = &yellow_spots[i*6];
    valids[i] = 0;
  }
  red_win = false;
  yellow_win = false;

}

void Board::make_move(bool p, int i)
{
  if(p)
  {
    red_entry[i][valids[i]] = true;
    valids[i]++;
  }
  else
  {
    yellow_entry[i][valids[i]] = true;
    valids[i]++;
  }
}



void Board::print()
{
  for (int j = 5; j > -1; j--)
  {
    for (int i = 0; i < 7; i++)
    {
      if (j<valids[i])
      {
        if (red_entry[i][j])
        {
          std::cout << "\033[31m" << " o " << "\033[0m";
        }
        else
        {
          std::cout << "\033[33m" << " o " << "\033[0m";
        }
      }
      else if(j==valids[i])
      {
        std::cout << "\033[32m" << " o " << "\033[0m";
      }
      else
      {
        std::cout << " o ";
      }
    }
    std::cout << std::endl;
  }
}

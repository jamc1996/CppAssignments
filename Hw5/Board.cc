#include <iostream>

#include "Board.h"

Board::Board(int n, int m) : nrows(n), ncols(m), red_spots(new bool[n*m]), yellow_spots(new bool[n*m]), red_entry(new bool*[m]), yellow_entry(new bool*[m]), red_win(false), yellow_win(false), valids(new int[m]), last_move(-1)
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

void Board::set_lastmove(int move)
{
  last_move = move;
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

void Board::unmake_move(bool p, int i)
{
  if(p)
  {
    red_entry[i][valids[i]-1] = false;
    valids[i]--;
  }
  else
  {
    yellow_entry[i][valids[i]-1] = false;
    valids[i]--;
  }
}

bool Board::check_win(bool** reds)
{
    for (int j = 0; j < 7; j++)
    {
      for (int i=0; i<4; i++)
      {
        if (reds[i][j])
        {
          if (reds[i+1][j])
          {
            if (reds [i+2][j])
            {
              if (reds[i+3][j])
              {
                return true;
              }
              i++;
            }
            i++;
          }
          i++;
        }
      }
    }
    for (int i = 0; i < 7; i++)
    {
      for (int j=0; j<4; j++)
      {
        if (valids[i]<(j+4))
        {
          break;
        }
        if (reds[i][j])
        {
          if (reds[i][j+1])
          {
            if (reds[i][j+2])
            {
              if (reds[i][j+3])
              {
                return true;
              }
              j++;
            }
            j++;
          }
          j++;
        }
      }
    }
    for (int i = 0; i < 4; i++)
    {
      for (int j=0; j<4; j++)
      {
        if (reds[i][j] && reds[i+1][j+1] && reds[i+2][j+2] && reds[i+3][j+3])
        {
          return true;
        }
      }
    }
    for (int i = 0; i < 4; i++)
    {
      for (int j=3; j<7; j++)
      {
        if (reds[i][j] && reds[i+1][j-1] && reds[i+2][j-2] && reds[i+3][j-3])
        {
          return true;
        }
      }
    }
    return false;
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

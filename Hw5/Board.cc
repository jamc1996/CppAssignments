#include "board.h"


/*      board.cc -- program with Board class for Connect4 games.
 *
 *      Author:     John Cormican
 *
 *      Purpouse:   To allow user to play against computer through terminal.
 *
 *      Usage:      Methods called from main.cc and player.cc to simulate
 *                  playing of Connect4 on a real board.
 *
 */

Board::Board(int n, int m) : nrows(n), ncols(m), red_spots(new bool[n*m]), yellow_spots(new bool[n*m]), red_entry(new bool*[m]), yellow_entry(new bool*[m]), red_win(false), yellow_win(false), last_move(-1), valids(new int[m])
/* Initializer for Board class. */
{
  //Position stored as where red discs are, yellow discs are and valid moves are.
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
/* setter for last_move variable. */
{
  last_move = move;
}

void Board::make_move(bool p, int i)
/* Function to make a move on the board. */
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
/* Function to unmake a move (used by machine player on virtual board.) */
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

bool Board::check_win(bool** discs)
/* Function to check if a player has won. */
{
  // Check row wins
  for (int i=0; i<4; i++)
  {
    for (int j = 0; j < 6; j++)
    {
      if (j==valids[i])
      {
        break;
      }
      if (discs[i][j])
      {
        if (discs[i+1][j])
        {
          if (discs[i+2][j])
          {
            if (discs[i+3][j])
            {
              return true;
            }
          }
        }
      }
    }
  }

  // Check column wins
  for (int i = 0; i < 7; i++)
  {
    for (int j=0; j<3; j++)
    {
      if (valids[i]<(j+4))
      {
        break;
      }
      if (discs[i][j])
      {
        if (discs[i][j+1])
        {
          if (discs[i][j+2])
          {
            if (discs[i][j+3])
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

  //Check forward diagonal wins
  for (int i = 0; i < 4; i++)
  {
    for (int j=0; j<3; j++)
    {
      if (j==valids[i])
      {
        break;
      }
      if (discs[i][j] && discs[i+1][j+1] && discs[i+2][j+2] && discs[i+3][j+3])
      {
        return true;
      }
    }
  }

  // Check backwards diagonal wins.
  for (int i = 3; i < 7; i++)
  {
    for (int j=0; j<3; j++)
    {
      if (j==valids[i])
      {
        break;
      }
      if (discs[i][j] && discs[i-1][j+1] && discs[i-2][j+2] && discs[i-3][j+3])
      {
        return true;
      }
    }
  }
  return false;
}

bool Board::check_symmetry()
/* Function to check if the board is symmetric
 * (can half amount of computation).
 */
{
  for (int i = 0; i < 3; i++)
  {
    if (valids[i] != valids[6-i])
    {
      return false;
    }
    for (int j = 0; j < valids[i]; j++)
    {
      if (red_entry[i][j] != red_entry[6-i][j])
      {
        return false;
      }
    }
  }
  return true;
}

void Board::print()
/* Function to print the board. */
{
  std::cout << "-------------------------------" << '\n';
  for (int j = 5; j > -1; j--)
  {
    for (int i = 0; i < 7; i++)
    {
      std::cout << " | " ;
      if (j<valids[i])
      {
        if (red_entry[i][j])
        {
          std::cout << "\033[31m" << "o" << "\033[0m";
        }
        else
        {
          std::cout << "\033[33m" << "o" << "\033[0m";
        }
      }
      else
      {
        std::cout << "o";
      }
    }
    std::cout << " | "<< std::endl;
  }
  std::cout << "-------------------------------" << '\n';
}


Board::~Board()
{
  delete []red_entry;
  delete []yellow_entry;
  delete []red_spots;
  delete []yellow_spots;
  delete []valids;
}
 /*  WARNING/APOLOGY: The weights in the check_threats function were
      changed around a lot and might seem a bit strange. */

double Board::check_threats(Board* board, bool** mine, bool ** ops, bool to_play)
/*
 *    Function to check for threatening combinations of the opponent.
 *  I did a lot of fiddling with the values, so this is a bit of a mess
 */
{
  // threats represents total threat value on board.
  // threat_score represents threat along individual string
  double threats = 0.0;
  double threat_score;

  //Check row threats
  for (int j = 0; j < 6; j++)
  {
    for (int i=0; i<4; i++)
    {
      threat_score = 0;

      // If there is an opponent disc in string we can move on.
      if (ops[i][j])
      {
        continue;
      }
      if (ops[i+1][j])
      {
        i++;
        continue;
      }
      if (ops[i+2][j])
      {
        i+=2;
        continue;
      }
      if (ops[i+3][j])
      {
        i+=3;
        continue;
      }

      // The more discs we occupy the greater our threat
      for (int k = 0; k < 4; k++) {
        if (mine[i+k][j])
        {
          threat_score+=1;
        }
      }

      // Some weights added to insentivise future threats
      if (threat_score>2) {
        for (int k = 0; k < 4; k++) {
          if (to_play)
          {
            if (valids[i+k]==j)
            {
              threat_score+=0.7;
            }
            else if (valids[i+k]<j)
            {
              threat_score+=0.4;
            }
          }
          else
          {
            if (valids[i+k]<j)
            {
              threat_score+=0.4;
            }
          }
        }
      }
      else if (threat_score>0)
      {
        for (int k = 0; k < 4; k++) {
          if (to_play)
          {
            if (valids[i+k]==j)
            {
              threat_score+=0.2;
            }
            else if (valids[i+k]<j)
            {
              threat_score+=0.1;
            }
          }
          else
          {
            if (valids[i+k]<j)
            {
              threat_score+=0.1;
            }
          }
        }
      }

      // We lessen weight to avoid double counting:
      if (threat_score>2.91 && i<3) {
        if(mine [i+4][j])
        {
          threat_score/=2;
        }
      }
      if (threat_score>2.8) {
        threat_score+=0.2;
      }

      // threats incremented by required amount
      threats+=((threat_score)*(threat_score));
    }
  }
  // Check column threats
  for (int i = 0; i < 7; i++)
  {
    for (int j=0; j<3; j++)
    {
      threat_score = 0;
      if (ops[i][j])
      {
        continue;
      }
      if (ops[i][j+1])
      {
        j++;
        continue;
      }
      if (ops[i][j+2])
      {
        j+=2;
        continue;
      }
      if (ops[i][j+3])
      {
        j+=3;
        continue;
      }
      for (int k = 0; k < 4; k++)
      {
        if (mine[i][j+k])
        {
          threat_score+=1;
        }
      }
      // Having a long column together is dangerous as leads to a lot of
      // diagonal and row threats.
      if (threat_score > 1 && to_play)
      {
        threat_score+=2;
      }

      // threats incremented by weighted total.
      // squaring motivates long strings instead of multiple short strings
      threats+=((threat_score)*(threat_score));
    }
  }
  // Check for threats along diagonal
  for (int i = 0; i < 4; i++)
  {
    for (int j=0; j<3; j++)
    {
      threat_score = 0;
      if (ops[i][j] || ops[i+1][j+1] || ops[i+2][j+2] || ops[i+3][j+3])
      {
        continue;
      }
      for (int k = 0; k < 4; k++) {
        if (mine[i+k][j+k])
        {
          threat_score+=1;
        }
      }
      if (threat_score>2) {
        for (int k = 0; k < 4; k++) {
          if (to_play)
          {
            if (valids[i+k]==j+k)
            {
              threat_score+=0.7;
            }
            else if (valids[i+k]<j+k)
            {
              threat_score+=0.4;
            }
          }
          else
          {
            if (valids[i+k]<j+k)
            {
              threat_score+=0.4;
            }
          }
        }
      }
      else if (threat_score>0)
      {
        for (int k = 0; k < 4; k++) {
          if (to_play)
          {
            if (valids[i+k]==j+k)
            {
              threat_score+=0.2;
            }
            else if (valids[i+k]<j+k)
            {
              threat_score+=0.1;
            }
          }
          else
          {
            if (valids[i+k]<j+k)
            {
              threat_score+=0.1;
            }
          }
        }
      }
      if (threat_score>2.91 && i<3 && j<2 )
      {
        if (mine [i+4][j+4])
        {
          threat_score/=2.0;
        }
      }
      if (threat_score>2.91)
      {
        threat_score+=0.2;
      }
      // squaring motivates long strings instead of multiple short strings
      threats+=((threat_score)*(threat_score))*1.2;
    }
  }
  // Threats calculated along backwards diagonals
  for (int i = 3; i < 7; i++)
  {
    for (int j=0; j<3; j++)
    {
      threat_score = 0;

      // Check for opponents discs and move on if necessary
      if (ops[i][j] || ops[i-1][j+1] || ops[i-2][j+2] || ops[i-3][j+3])
      {
        continue;
      }

      for (int k = 0; k < 4; k++) {
        if (mine[i-k][j+k])
        {
          threat_score+=1;
        }
      }

      // Weights changed around to improve performance:
      if (threat_score>2) {
        // insentivise strings fo 3
        for (int k = 0; k < 4; k++) {
          if (to_play)
          {
            if (valids[i-k]==j+k)
            {
              threat_score+=0.7;
            }
            else if (valids[i-k]<j+k)
            {
              threat_score+=0.4;
            }
          }
          else
          {
            if (valids[i-k]<j+k)
            {
              threat_score+=0.4;
            }
          }
        }

      }
      //Weights changed for strings
      else if (threat_score>0)
      {
        for (int k = 0; k < 4; k++) {
          if (to_play)
          {
            if (valids[i-k]==j+k)
            {
              threat_score+=0.2;
            }
            else if (valids[i-k]<j+k)
            {
              threat_score+=0.1;
            }
          }
          else
          {
            if (valids[i-k]<j+k)
            {
              threat_score+=0.1;
            }
          }
        }
      }
      // Check for double adding of threats
      if (threat_score>2.91 && i>4 && j<2)
      {
        if (mine [i-4][j+4])
        {
          threat_score/=2.0;
        }
      }
      if (threat_score>2.91)
      {
        threat_score+=0.2;
      }
      if (threat_score>1) {
        for (int k = 0; k < 4; k++) {
          if (valids[i-k]<j+k)
          {
            threat_score+=0.1;
          }
        }
      }

      // Weighted total added
      // squaring motivates long strings instead of multiple short strings

      threats+=(threat_score)*(threat_score)*1.3;
    }
  }
  return threats;
}

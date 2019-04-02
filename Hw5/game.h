#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"

/*    game.h -- header file with Game class
 *
 *    Author: John Cormicna
 */

class Game
{
private:
  Player* red_player;
  Player* yellow_player;
  Board* board;

public:
  Game(Player* red_player, Player* yellow_player, Board* board);
  void play();
  void print_result();
  ~Game();
};

#endif

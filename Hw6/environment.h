#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "fish.h"
#include <vector>
#include <list>
#include <map>




//Typedefs to simplify function arguments
typedef std::multimap <int, Fish*>::iterator fishy_iter;
typedef std::pair<fishy_iter, fishy_iter> fishy_pair;

class Environment
{
private:
  int dims[3];
  int n_fish;
  int n_living_fish;
  std::multimap <int, Fish* > fish_map;
  std::list<int> fish_ids[3];


public:
  Environment(int dim_array[3], int nu_fish[3]);

  template <class myFish>
  void add_fish(int new_fish, int type);
  template <class myFish>
  void add_fish(int new_fish, int key, int type);

  void feeding_frenzy(int key);
  int pick_random(std::list<int> ids);
  void move_rand_fish();
  int move_fish(int mover);

  void update_step(int key);
  void count_fish_types(int cell_fish[5], int key, fishy_pair res);
  int pick_possibility(int cell_fish[5]);
  void enact_update(int c, int key, int n_tuna, fishy_pair res);
  void kill_fish(fishy_iter it, int id, int type);

  void list_fish();
  void key_to_pos(int key, int pos[3]);
};

#endif

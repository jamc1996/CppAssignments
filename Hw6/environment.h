#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "fish.h"
#include <vector>
#include <list>
#include <map>


class Environment
{
private:
  int n_fish;
  std::multimap <int, Fish* > fish_map;
  std::list<int> fish_ids[3];
  int dims[3];

public:
  Environment(int dim_array[3], int nu_fish[3]);

  void key_to_pos(int key, int pos[3]);


  void add_minnows(int n_minnows);
  void add_minnows(int n_minnows, int key);

  void list_fish();
  void add_tuna(int n_tuna);
  void add_sharks(int n_sharks);

  void map_minnow(int fish_pos[3], int n_fish);
  void move_rand_fish();
  int pick_random(std::list<int> ids);
  void update_step(int key);
};

#endif

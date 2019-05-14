#include "environment.h"

Environment::Environment(int dim_array[3], int nu_fish[3])
/* Constructor for Environment class. */
{

  n_fish = 0;
  n_living_fish = 0;
  for (size_t i = 0; i < 3; i++) {
    dims[i] = dim_array[i];
  }

  //Population added:
  add_fish<Minnow>(nu_fish[0],0);
  add_fish<Tuna>(nu_fish[1],1);
  add_fish<Shark>(nu_fish[2],2);

  std::cout << "Enivornment Created!" << '\n';
}



template <class myFish>
void Environment::add_fish(int new_fish, int type)
/*  Overloaded template to create any of minnow, tuna or shark.
 *  Places (new_fish) fish in random location.
 */
{
  int key;
  int fish_pos[3];
  //#pragma omp for
  for (size_t i = 0; i < new_fish; i++)
  {
    for (size_t j = 0; j < 3; j++)
    {
      fish_pos[j] = rand()%dims[j];
    }
    key = fish_pos[0]*dims[1]*dims[2] + fish_pos[1]*dims[2] + fish_pos[2];

    // New fish created and inserted into multimap
    fish_map.insert(std::make_pair(key,new myFish(fish_pos, dims, n_fish)));

    // Population values updated in Environment
    fish_ids[type].push_back(n_fish);
    n_fish++;
    n_living_fish++;
  }
}

template <class myFish>
void Environment::add_fish(int new_fish, int key, int type)
/*  Overloaded template to create any of minnow, tuna or shark.
 *  Places (new_fish) fish in specific location based on key.
 */
{
  int fish_pos[3];
  key_to_pos(key, fish_pos);
  for (size_t i = 0; i < new_fish; i++)
  {
    fish_map.insert(std::make_pair(key,new myFish(fish_pos, dims, n_fish)));
    fish_ids[type].push_back(n_fish);
    n_fish++;
    n_living_fish++;
  }
}


void Environment::move_rand_fish()
/*  Function to move a random fish with probability 0.9.
 */
{
  // Probability that a fish will move = 0.9:
  int y = rand()%10;
  if(y<9)
  {
    // Equal probability of each type to move:
    int x = rand()%3;

    // Individual to move chosen:
    int mover = pick_random(fish_ids[x]);
    if (mover < 0) {
      //If the species is extinct nothing moves.
      return;
    }
    // Selected fish is moved:
    std::cout << "Mover is " << mover << '\n';
    int key = move_fish(mover);

    if (key < 0) {
      printf("ok\n");
      return;
    }

    std::cout << "key is " << key << '\n';
list_fish();
    // Environment is updated based on the move:
    update_step(key);
    std::cout << "ok" << '\n';
  }
}

int Environment::move_fish(int mover)
/*  Function to move a fish of any type given its fish_id.
 *  Returns the key to the new position of the fish.
 */
{
  int key=-1;
  for(std::multimap<int,Fish*>::iterator it = fish_map.begin(); it != fish_map.end(); it++){
    //it->first retrieves key and it->second retrieves value
    if(it->second->fish_id == mover)
    {
      // If tuna/shark is at starvation_level 4 it will die on next move.
      std::cout << "type is " << it->second->type << '\n';

      if (it->second->type>0 && it->second->starvation_level==4)
      {
        std::cout << "starving" << it->second->type << '\n';
        kill_fish(it,mover,it->second->type);
        return -1;
      }
      // Fish moves and key is updated:

      (it->second)->move();
      key = (it->second)->calc_key();

      // Map is updated:
      std::cout << "inserting" << '\n';
      fish_map.insert(std::make_pair(key,it->second));
      std::cout << "type is " << it->second->type << '\n';

      fish_map.erase(it);
      break;
    }
  }
  return key;
}

int Environment::pick_random(std::list<int> ids)
/* Function to pick a random integer from a list of ints.
 */
{
  std::list<int>::iterator it = ids.begin();
  int sz = ids.size();
  if (sz>0) {
    int x = rand()%sz;
    std::advance(it,x);
    return *it;
  }
  return -1;
}

void Environment::update_step(int key)
/*  Function to update the environment at location based on key.
 */
{
  int cell_fish[5]={0};
  std::pair<fishy_iter, fishy_iter> res = fish_map.equal_range(key);

  // Update option chosen based on entries at location:
  count_fish_types(cell_fish,key,res);
  int choice = pick_possibility(cell_fish);

  // Update is enacted if any options available:
  if (choice > 0) {
    enact_update(choice, key, cell_fish[1], res);
  }
  std::cout << "??" << '\n';
}

void Environment::count_fish_types(int cell_fish[5], int key, fishy_pair res)
/*  Function to count fish types in cell and store in cell_fish.
 *  Categories are: Minnows, Tuna, Sharks, Breeding Tuna, Breeding Sharks.
 */
{
  // Iterate through key location in multimap:
  for (fishy_iter itr = res.first; itr != res.second; itr++)
  {
    cell_fish[(itr->second)->type ]++;
    if (itr->second->type > 0)
    {
      if (itr->second->has_eaten) {
        cell_fish[(itr->second->type)+2]++;
      }
    }
  }
}

int Environment::pick_possibility(int cell_fish[5])
/*  Function to choose which update based on fish at cell
 */
{
  // List of possibilities labeled with ints created/appended:
  std::list<int> possibilities;
  if (cell_fish[0]>1)
  {
    possibilities.push_back(1);
  }
  if (cell_fish[3]>1) {
    possibilities.push_back(2);
  }
  if (cell_fish[4]>1) {
    possibilities.push_back(3);
  }
  if (cell_fish[0]>0 && cell_fish[1]>0) {
    possibilities.push_back(4);
  }
  if(cell_fish[1]>0 && cell_fish[2]>0)
  {
    possibilities.push_back(5);
  }
  if(cell_fish[2]>0 && cell_fish[0]>0)
  {
    possibilities.push_back(6);
  }

  // If possibilites available, pick one at random:

  return pick_random(possibilities);
}

void Environment::enact_update(int c, int key, int n_tuna, fishy_pair res)
/*  Environment is updated according to the label c.
 */
{
  int counter, x;
  switch (c) {
    // Multiple minnows -> 3 new minnows:
    case 1:
      add_fish<Minnow>(3,key,0);
      break;

    // Multiple breeding tuna -> 1 new tuna:
    case 2:
      add_fish<Tuna>(1,key,1);
      break;

    // Multiple breeding sharks -> 1 new shark:
    case 3:
      add_fish<Shark>(1,key,1);
      break;

    // Tuna + Minnows -> tuna eats all minnows:
    case 4:
      std::cout << "time to kill minnows" << '\n';
      for (auto itr = res.first; itr != res.second; itr++)
      {
        std::cout << "ok" << '\n';
        if (itr->second->type == 0)
        {
          std::cout << "itr" << itr->second->fish_id << '\n';
          kill_fish(itr,itr->second->fish_id,0);
          res = fish_map.equal_range(key);
          itr = res.first;
        }
        if (itr->second->type == 1)
        {
          itr->second->eat();
        }
      }
      break;

    // Shark + Tuna -> shark eats random tuna:
    case 5:
      x = rand()%n_tuna;
      counter = 0;
      for (auto itr = res.first; itr != res.second; itr++)
      {
        if (itr->second->type == 1)
        {
          if (counter == x) {
            std::cout << "itr" << itr->second->fish_id << '\n';
            kill_fish(itr,itr->second->fish_id,1);
            res = fish_map.equal_range(key);
            itr = res.first;
          }
        }
        if (itr->second->type == 2)
        {
        //  itr->second->eat();
        }
        counter++;
      }
      break;
    // Shark + minnows present -> start feeding frenzy
    case 6:
      feeding_frenzy(key);
      break;
  }
  std::cout << "step almost complete" << '\n';

}

void Environment::feeding_frenzy(int key)
{
  std::cout << "Frenzy beginning!" << '\n';
  int pos[3];
  key_to_pos(key, pos);
  int kp = key - dims[2]*dims[1] - dims[1] - 1;
  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (kp<0) {
          kp+=dims[0]*dims[1]*dims[2];
        }
        else if(kp>=dims[0]*dims[1]*dims[2])
        {
          kp-=dims[0]*dims[1]*dims[2];
        }
        fishy_pair res = fish_map.equal_range(kp+j);
        for (auto itr = res.first; itr != res.second; itr++)
        {
          if (itr->second->type == 0)
          {
            if (itr->second->type == 0)
            {
              std::cout << "itr" << itr->second->fish_id << '\n';
              kill_fish(itr,itr->second->fish_id,0);
              res = fish_map.equal_range(key);
              itr = res.first;
            }
            if(kp == key)
            {
              if (itr->second->type == 2)
              {
                //itr->second->eat();
              }
            }
          }
        }
        kp+=dims[1];
      }
      kp+=dims[1]*dims[2];
    }
  }
}

void Environment::key_to_pos(int key, int pos[3])
{
  pos[0] = key/(dims[1]*dims[2]);
  pos[1] = (key/dims[2])%dims[0];
  pos[2] = key%(dims[0]*dims[1]);
}


void Environment::kill_fish(fishy_iter it, int id, int type)
{
  std::cout << "Goodbye Cruel World :'('" << it->second->fish_id << '\n';
  fish_map.erase(it);
  fish_ids[type].remove(id);
  n_living_fish--;
}


void Environment::list_fish()
/*  Function to list all the living fish with they key to their position
 *  Minnows are coloured green, tuna yellow and sharks red.
 */
{
  std::cout << "There are " << n_living_fish << " fish." << std::endl;
  for (std::multimap<int,Fish*>::iterator it=fish_map.begin(); it!=fish_map.end(); ++it)
  {
    if((*it).second->type==0)
    {
      std::cout << "\033[32m" << (*it).first << " => " << (*it).second->fish_id << "\033[0m" << '\n';
    }
    else if((*it).second->type==1)
    {
      std::cout << "\033[33m" << (*it).first << " => " << (*it).second->fish_id << "\033[0m" << '\n';
    }
    else if((*it).second->type==2)
    {
      std::cout << "\033[31m" << (*it).first << " => " << (*it).second->fish_id << "\033[0m" << '\n';
    }
  }
}

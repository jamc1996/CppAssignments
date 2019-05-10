#include "environment.h"

Environment::Environment(int dim_array[3], int nu_fish[3])
{
  n_fish = 0;
  for (size_t i = 0; i < 3; i++) {
    dims[i] = dim_array[i];
  }
  add_minnows(nu_fish[0]);
  //add_tuna(nu_fish[1]);
  //add_sharks(nu_fish[2]);
  std::cout << "Enivornment Created!" << '\n';
}

void Environment::add_minnows(int n_minnows)
{
    //#pragma omp for
    for (size_t i = 0; i < n_minnows; i++)
    {
      int fish_pos[3];
      for (size_t j = 0; j < 3; j++)
      {
        fish_pos[j] = rand()%dims[j];
      }
      map_fish<Minnow>(fish_pos, n_fish);
      fish_ids[0].push_back(n_fish);
      n_fish++;
    }
}

void Environment::key_to_pos(int key, int pos[3])
{
  pos[0] = key/(dims[1]*dims[2]);
  pos[1] = (key/dims[2])%dims[0];
  pos[2] = key%(dims[0]*dims[1]);
}

void Environment::add_minnows(int n_minnows, int key)
{
    //#pragma omp for
    int fish_pos[3];
    key_to_pos(key,fish_pos);
    for (size_t i = 0; i < n_minnows; i++)
    {
      map_fish<Minnow>(fish_pos, n_fish);
      fish_ids[0].push_back(n_fish);
      n_fish++;
    }
}

template <class myFish>
void Environment::map_fish(int fish_pos[3], int n_fish)
{
  int key = fish_pos[0]*dims[1]*dims[2] + fish_pos[1]*dims[2] + fish_pos[2];
  fish_map.insert(std::make_pair(key,new myFish(fish_pos, dims, n_fish)));
}


void Environment::list_fish()
{
  std::cout << "There are " << n_fish << " fish." << std::endl;
  for (std::multimap<int,Fish*>::iterator it=fish_map.begin(); it!=fish_map.end(); ++it)
  {
    std::cout << (*it).first << " => " << (*it).second->fish_id << '\n';
  }
}


void Environment::move_rand_fish()
{
  int x;
  x = 0;//rand()%3;

  int mover = pick_random(fish_ids[x]);
  int key=-1;

  for(std::multimap<int,Fish*>::iterator it = fish_map.begin(); it != fish_map.end(); it++){
    //it->first retrieves key and it->second retrieves value
    if(it->second->fish_id == mover)
    {
      (it->second)->move();
      key = (it->second)->calc_key();

      fish_map.insert(std::make_pair(key,it->second));
      fish_map.erase(it);
      break;
    }
  }
  update_step(key);
}

int Environment::pick_random(std::list<int> ids)
{
  std::list<int>::iterator it = ids.begin();
  int x = rand()%(ids.size());
  std::advance(it,x);
  return *it;
}

void Environment::update_step(int key)
{
  int cell_fish[5]={0};
  typedef std::multimap <int, Fish*>::iterator fishy_iter;
  std::pair<fishy_iter, fishy_iter> res = fish_map.equal_range(key);
  for (fishy_iter itr = res.first; itr != res.second; itr++)
  {
    cell_fish[(itr->second)->type ]++;
  }
  if (cell_fish[0]>1)
  {
    add_minnows(3,key);
  }
}

#include "fish.h"

int Fish::calc_key()
{
  return coord[0]*fdim[1]*fdim[2] + coord[1]*fdim[2] + coord[2];
}


Fish::~Fish()
{

}

Minnow::Minnow(int coord_a[3], int dims[3], int id)
{
  fish_id = id;
  type = 0;
  for (size_t i = 0; i < 3; i++) {
    coord[i] = coord_a[i];
    fdim[i] = dims[i];
  }
}

void Minnow::move()
{
  // Minnow can move to any of 26 adjacent squares
  int x = rand() %26;

  // Probablities chosen so:
  // moves back = 9/26
  // move forward = 9/26
  // no move in given dir = 8/26

  if (x < 9)
  {
    coord[0]--;
  }
  else if ( x < 18)
  {
    coord[0]++;
  }

  if (x%3 == 0)
  {
    coord[1]--;
  }
  else if (x%3 == 1)
  {
    coord[1]++;
  }

  if (((x%9)/3)==0)
  {
    coord[2]--;
  }
  else if (((x%9)/3)==1)
  {
    coord[2]++;
  }

  // Finally make sure obey periodic boundary conditions:
  for (int i = 0; i < 3; i++)
  {
    if (coord[i]<0)
    {
      coord[i] = fdim[i] - 1;
    }
    else if(coord[i] >= fdim[i])
    {
      coord[i] = 0;
    }
  }
}

Tuna::Tuna(int coord_a[3], int dims[3], int id) /*: coord{coord_a[0], coord_a[1], coord_a[2]}, fdim{dims[0], dims[1], dims[2]}*/
{
  fish_id = id;
  type = 1;
  has_eaten = false;
  starvation_level = 0;
  for (size_t i = 0; i < 3; i++)
  {
    coord[i] = coord_a[i];
    fdim[i] = dims[i];
  }
}

//int Tuna::get_starvation(){ return starvation_level;  }

//bool Tuna::get_haseaten() const {  return has_eaten;}

//bool Shark::get_haseaten() const {  return has_eaten;}

//int Shark::get_starvation(){  return starvation_level;}

Shark::Shark(int coord_a[3], int dims[3], int id)
{
  fish_id = id;
  type = 2;
  has_eaten = false;
  starvation_level = 0;
  for (size_t i = 0; i < 3; i++)
  {
    coord[i] = coord_a[i];
    fdim[i] = dims[i];
  }
}

void Tuna::eat()
{
  has_eaten=true;
  starvation_level=0;
}

void Shark::eat()
{
  has_eaten=true;
  starvation_level=0;
}

void Shark::move()
{
  // For sharks it was much easier to just generate two random numbers
  int x = rand() % 6;
  int y = rand() % 4;
  int dim1 = x%3;
  int dir1 = x/3;
  int dim2 = (y%2)+1;
  int dir2 = y%2;
  if (dir1==0)
  {
    coord[dim1]+=2;
  }
  else
  {
    coord[dim1]-=2;
  }
  if (dir2 == 0)
  {
    coord[(dim1+dim2)%3]--;
  }
  else
  {
    coord[(dim1+dim2)%3]++;
  }
  for (int i = 0; i < 3; i++) {
    if (coord[i]<0) {
      coord[i]+=fdim[i];
    }
    else if(coord[i]>=fdim[i]){
      coord[i]-=fdim[i];
    }
  }
  starvation_level++;
  printf("%d starvation level %d\n", type, starvation_level);
}

void Tuna::move()
{
  //Tuna move planar diagonal -> two dimensions change, 1 held constant.
  //                          -> 12 possible moves
  int x = rand() %12;
  int unchanged_dim;
  if (x < 4)
  {
    unchanged_dim = 0;
  }
  else if (x<8)
  {
    unchanged_dim = 1;
  }
  else if (x<8)
  {
    unchanged_dim = 2;
  }

  if ((x%4)/2 == 0)
  {
    coord[(unchanged_dim+1)%3]--;
  }
  else
  {
    coord[(unchanged_dim+1)%3]++;
  }

  if ((x%4)%2 == 0)
  {
    coord[(unchanged_dim+2)%3]--;
  }
  else
  {
    coord[(unchanged_dim+2)%3]++;
  }

  for (int i = 0; i < 3; i++)
  {
    if (coord[i]<0)
    {
      coord[i] = fdim[i]-1;
    }
    else if(coord[i] >= fdim[i])
    {
      std::cout << "i is " << i << "coord[i] is "  << coord[i] << '\n';
      coord[i] = 0;
    }
  }
  std::cout << fdim[0] << fdim[1] << fdim[2] << '\n';

  std::cout << coord[0] << coord[1] << coord[2] << '\n';

  starvation_level++;
  printf("%d starvation level %d\n", type, starvation_level);
}

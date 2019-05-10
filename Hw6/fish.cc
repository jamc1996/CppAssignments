#include "fish.h"

int Fish::calc_key()
{
  return coord[0]*fdim[1]*fdim[2] + coord[1]*fdim[2] + coord[2];
}

Minnow::Minnow(int coord_a[3], int dims[3], int id) /*: coord{coord_a[0], coord_a[1], coord_a[2]}, fdim{dims[0], dims[1], dims[2]}*/
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
  int x = rand() %26;

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

  for (size_t i = 0; i < 3; i++)
  {
    if (coord[i]<0)
    {
      coord[i] = fdim[i] - 1;
    }
    else if(coord[i] == fdim[i])
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
  for (size_t i = 0; i < 3; i++)
  {
    coord[i] = coord_a[i];
    fdim[i] = dims[3];
  }
  std::cout << "Tuna created!" << '\n';
}

Shark::Shark(int coord_a[3], int dims[3], int id)
{
  fish_id = id;
  type = 2;
  has_eaten = false;
  starvation_level = 0;
  for (size_t i = 0; i < 3; i++)
  {
    coord[i] = coord_a[i];
    fdim[i] = dims[3];
  }
  std::cout << "Shark created!" << '\n';
}

void Shark::move()
{
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
}

void Tuna::move()
{
  int x = rand() %8;

  if (x < 4)
  {
    coord[0]--;
  }
  else
  {
    coord[0]++;
  }

  if (x%2 == 0)
  {
    coord[1]--;
  }
  else
  {
    coord[1]++;
  }

  if ((x%4)/2 == 0)
  {
    coord[2]--;
  }
  else
  {
    coord[2]++;
  }

  for (size_t i = 0; i < 3; i++)
  {
    if (coord[i]<0)
    {
      coord[i] = fdim[i] - 1;
    }
    else if(coord[i] == fdim[i])
    {
      coord[i] = 0;
    }
  }
}

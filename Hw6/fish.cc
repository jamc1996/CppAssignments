#include "fish.h"

/*      fish.cc -- functions for Fish classes.
 *
 *      Author:     John Cormican
 *
 *      Purpouse:   To simulate different types of fish.
 *
 *      Usage:      Methods called from a Environment to change/give information
 *                  about the fish.
 */

// Base Fish functions:
int Fish::calc_key()
/* Returns the key of fishes location from 3-d position. */
{
  return coord[0]*fdim[1]*fdim[2] + coord[1]*fdim[2] + coord[2];
}

Fish::~Fish(){
}

// Minnows functions


Minnow::Minnow(int coord_a[3], int dims[3], int id)
/* Constructor for Minnow class. */
{
  fish_id = id;
  type = 0;
  for (size_t i = 0; i < 3; i++) {
    coord[i] = coord_a[i];
    fdim[i] = dims[i];
  }
}

void Minnow::move()
/* Function to simulate minnow moving. */
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

Minnow::~Minnow()
{

}

// Tuna Functions:

Tuna::Tuna(int coord_a[3], int dims[3], int id)
/* Constructor for Tuna class. */
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

void Tuna::move()
/* Function to simulate a Tuna moving.*/
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
  else
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

  // Periodic boundary conditions observed:
  for (int i = 0; i < 3; i++)
  {
    if (coord[i]<0)
    {
      coord[i] = fdim[i]-1;
    }
    else if(coord[i] >= fdim[i])
    {
      coord[i] = 0;
    }
  }

  // Starvation level goes up.
  starvation_level++;
}


void Tuna::eat()
/* Function to simulate a Tuna eating. */
{
  has_eaten=true;
  starvation_level=0;
}

Tuna::~Tuna(){
}

//Shark Functions:

Shark::Shark(int coord_a[3], int dims[3], int id)
/* Constructor for Shark class. */
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

void Shark::move()
/* Function to simulate a shark moving. */
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

  // Periodic boundary conditions observed:
  for (int i = 0; i < 3; i++) {
    if (coord[i]<0) {
      coord[i]+=fdim[i];
    }
    else if(coord[i]>=fdim[i]){
      coord[i]-=fdim[i];
    }
  }

  // Starvation level increases:
  starvation_level++;
}

void Shark::eat()
/* Function to simulate a shark eating. */
{
  has_eaten=true;
  starvation_level=0;
}

Shark::~Shark(){
}

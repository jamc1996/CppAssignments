#ifndef FISH_H
#define FISH_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

class Fish
{
  friend class Environment;
protected:
  int fish_id;
  int type;
  int coord[3];
  int fdim[3];
public:
  virtual void move()=0;
  int calc_key();
};

class Minnow : public Fish
{
private:

public:
  Minnow(int coord_a[3], int dims[3], int id);
  void move();
};


class Tuna : public Fish
{
private:
  bool has_eaten;

public:
  Tuna(int coord_a[3], int dims[3], int id);
  void move();
};

class Shark : Fish
{
private:
  bool has_eaten;
  bool starvation_level;

public:
  Shark(int coord_a[3], int dims[3], int id);
  void move();
};

#endif

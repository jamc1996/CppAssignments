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
  int starvation_level;
  bool has_eaten;
public:
  virtual void move()=0;
  virtual void eat(){return;};
  int calc_key();
  ~Fish();
  //virtual int get_starvation() const {return 0;};
  //virtual bool get_haseaten() const {return false;};
  //virtual void eat() { return; };

};

class Minnow : public Fish
{
private:

public:
  Minnow(int coord_a[3], int dims[3], int id);
  void move();
  ~Minnow();
};


class Tuna : public Fish
{
private:

public:
  Tuna(int coord_a[3], int dims[3], int id);
  void move();
  //int get_starvation() const {return starvation_level;};
  //bool get_haseaten() const {return has_eaten;};
  void eat();
  ~Tuna();
};

class Shark : public Fish
{
private:


public:
  Shark(int coord_a[3], int dims[3], int id);
  void move();
  //int get_starvation() const {return starvation_level;};
  //bool get_haseaten() const {return has_eaten;};
  void eat();
  ~Shark();
};

#endif

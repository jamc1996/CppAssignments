#include "environment.h"
#include "fish.h"


int main(int argc, char *argv[])
{
  int dims[3] = {5,5,5};
  int nfish[3] = {16,6,3};

  Environment Ocean(dims, nfish);
  std::cout << "\nInitial Position" << '\n';
  Ocean.list_fish();

  for (size_t i = 0; i < 10; i++) {
    Ocean.move_rand_fish();
    //std::cout << "\nAfter move " << i+1 << '\n';
  }
  Ocean.list_fish();
  return 0;
}

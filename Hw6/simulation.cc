#include "simulation.h"

/*    simulation.cc -- functions for Simulation class.
 *
 *    Author: John Cormican
 *
 *    Purpouse: To run a simulation of a fish tank
 *
 *    Usage:  Use constructor and then run() function to execute simulation.
 */

Simulation::Simulation(int dim_array[3], int nu_fish[3], int n, bool v) : n_iterations(n), verbose(v)
/* Constructor for Simulation class */
{
  for (size_t i = 0; i < 3; i++) {
    starting_conds[i] = nu_fish[i];
  }
  Ocean = new Environment(dim_array, nu_fish);
  if (verbose) {
    std::cout << "Final fish list" << '\n';
    Ocean->list_fish();
  }
}

void Simulation::run()
/* Function to run the simulation n iterations. */
{
  for (size_t i = 0; i < n_iterations; i++) {
    Ocean->move_rand_fish();
    if (verbose) {
      std::cout << "\nAfter move " << i+1 << ", there are:" << '\n';
      std::cout << Ocean->get_num(0) << " Minnows" << '\n';
      std::cout << Ocean->get_num(1) << " Tuna" << '\n';
      std::cout << Ocean->get_num(2) << " Sharks" << '\n';
    }
  }
  if (verbose) {
    std::cout << "Final fish list" << '\n';
    Ocean->list_fish();
  }
}

int Simulation::check_success()
/* Function to check for successful simulation (all species still alive). */
{
  for (size_t i = 0; i < 3; i++) {
    if (Ocean->get_num(i)==0) {
      std::cout << "At least one species is extinct." << '\n';
      if (!verbose) {
        std::cout << "Use -v flag for more information." << '\n';
      }
      return 0;
    }
  }

  std::cout << "Success!" << '\n';
  std::cout << "Initial Conditions:" << '\n';
  std::cout << starting_conds[0] << " Minnows" << '\n';
  std::cout << starting_conds[1] << " Tuna" << '\n';
  std::cout << starting_conds[2] << " Sharks" << '\n';
  if (!verbose) {
    std::cout << "Use -v flag for more information." << '\n';
  }

  return 1;
}


Simulation::~Simulation()
/* Destructor for Simulation class*/
{
  delete Ocean;
}

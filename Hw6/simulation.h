#ifndef SIMULATION_H
#define SIMULATION_H

#include "environment.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

/*    simulation.h -- header file for Simulation class.
 *
 *    Author: John Cormican
 */

class Simulation
{
private:
  int n_iterations;
  bool verbose;
  Environment* Ocean;
  int starting_conds[3];
public:
  Simulation(int dim_array[3], int nu_fish[3], int n, bool v);
  void run();
  int check_success();
  ~Simulation();
};

#endif

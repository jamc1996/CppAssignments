#include "environment.h"
#include "fish.h"
#include "simulation.h"

#include "unistd.h"

/*    main.cc -- main function for running simulations.
 *
 *    Author: John Cormican
 *
 *    Purpouse: To facilitate virtual fish tank.
 *
 *    Usage:  Run program with optional arguments.
 */

int main(int argc, char *argv[])
{
  // Default values set:
  int dims[3] = {5,5,5};
  int nfish[3] = {120,50,16};
  int iters = 1250;
  int c;
  bool verbose=false;

  // Getopt used to parse arguments:
  while ((c=getopt(argc,argv,"vm:s:t:i:"))!=-1) {
    switch (c) {
      case 'v':
        verbose = true;
        break;
      case 'm':
        nfish[0] = atoi(optarg);
        break;
      case 's':
        nfish[2] = atoi(optarg);
        break;
      case 't':
        nfish[1] = atoi(optarg);
        break;
      case 'i':
        iters = atoi(optarg);
        break;
    }
  }

  // Simulation class runs:
  Simulation simul(dims, nfish,iters,verbose);
  simul.run();
  simul.check_success();

  return 0;
}

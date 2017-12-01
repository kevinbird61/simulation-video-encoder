/** define global function for simulation operation
    expon: return an exponential random number
*/
#ifndef RANDOM_GEN
#define RANDOM_GEN

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lcgrand.h"

float expon(float mean);

#endif
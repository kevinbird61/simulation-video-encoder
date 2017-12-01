#ifndef QUEUE_
#define QUEUE_

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "state_var.h"

// define queue structure/operator
frame_frac *header;

// operator
void init();
int push(frame_frac *element);
frame_frac *pop();
frame_frac *pop_last();
void print_all();

#endif
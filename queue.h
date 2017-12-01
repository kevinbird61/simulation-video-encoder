#ifndef QUEUE_
#define QUEUE_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "state_var.h"

/* Define state variable data type */
#define TOP_SIZE 1
#define BOT_SIZE 2
#define field_size(type) (type==0)?TOP_SIZE:BOT_SIZE;
// define queue structure/operator
frame_frac *header;

// operator
void init();
int create_and_push(int type, inter_t timestamp);
int push(frame_frac *element);
int get_size();
frame_frac *pop();
frame_frac *pop_back();
void print_all();
void print_node(frame_frac *p);

#endif
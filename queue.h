#ifndef QUEUE_
#define QUEUE_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "state_var.h"
#include "random_gen.h"

/* Define state variable data type */
/* define queue structure/operator
    header -> total event queue list
    buffer_queue -> contain top,bottom field queue
    storage_queue -> contain the encoded top,bottom field queue
*/
frame_frac *event_queue;
frame_frac *buffer_queue;
frame_frac *storage_queue;

// operator
void init();
void drop(frame_frac *ptr);
void drop_all();
int create_and_push(frame_frac *ptr,int type, inter_t timestamp);
int create_push_sort(frame_frac *ptr,int type, float size, inter_t timestamp);
int push(frame_frac *ptr,frame_frac *element);
int push_sort(frame_frac *ptr,frame_frac *element);
int get_size(frame_frac *ptr);
frame_frac *pop(frame_frac *ptr);
frame_frac *pop_back(frame_frac *ptr);
void print_all(frame_frac *ptr);
void print_node(frame_frac *p);

#endif
/* Project 1 main entry - video frame encoder */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lcgrand.h"
#include "state_var.h"
#include "random_gen.h"

/** ================= define global state variable for simulation =================

    float sim_time: system simulation clock
    float time_last_event: 
    int buffer_size: encoder buffer size (need to fetch from user input)
    float mean: mean value of simulation (need to fetch from user input)
    frame_frac buffer_queue: buffer queue of encoder

*/
float mean = 0.1,sim_time = 0,time_last_event;
int buffer_size;

/** ================= define individual process function here =================

    float schedule_top();
    float schedule_bot();
*/


int main(){
    frame_frac pieces[10];

    for(int i=0;i<10;i++){
        pieces[i].type = i%2;
        pieces[i].size = field_size(i%2);
        pieces[i].timestamp = expon(mean);
    }

    for(int i=0;i<10;i++)
        printf("%d,size=%d,time=%f\t",pieces[i].type,pieces[i].size,pieces[i].timestamp);
    
    return 0;
}
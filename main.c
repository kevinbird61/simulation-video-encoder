/* Project 1 main entry - video frame encoder */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include "lcgrand.h"
#include "state_var.h"
#include "random_gen.h"
#include "queue.h"

extern char *optarg;
extern int optind, opterr, optopt;

/** ================= define global state variable for simulation =================

    float sim_time: system simulation clock
    float time_last_event: 
    int buffer_size: encoder buffer size (need to fetch from user input)
    float mean: mean value of simulation (need to fetch from user input)
    frame_frac buffer_queue: buffer queue of encoder

*/
float mean = 0.1,sim_time = 0,time_last_event;

float total_sim_time = 0.0;
int buffer_size;

/** ================= define individual process function here =================

    float schedule_top();
    float schedule_bot();
*/


int main(int argc,char *argv[]){

    int opt;
    int nsecs, tfnd;

    while((opt = getopt(argc,argv,"n:t:h"))!=-1){
        switch(opt){
            case 'n':
                // buffer size need to plus 1
                buffer_size = atoi(optarg) + 1;
                break;
            case 't':
                total_sim_time = atof(optarg);
                break;
            case 'h':
                fprintf(stdout,
                    "Usage: %s [-t time] [-n number]\n"
                    ,argv[0]);
                exit(1);
                break;
            default:
                fprintf(stderr,"Usage: %s [-t time] [-n number]\n",argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    printf("Buffer Size=%d\nTotal Simulation time=%f\n",buffer_size,total_sim_time);

    frame_frac pieces[10];

    for(int i=0;i<10;i++){
        pieces[i].type = i%2;
        pieces[i].size = field_size(i%2);
        pieces[i].timestamp = expon(mean);
    }

    for(int i=0;i<10;i++)
        printf("%d,size=%d,time=%f\n",pieces[i].type,pieces[i].size,pieces[i].timestamp);
    
    init();

    return 0;
}
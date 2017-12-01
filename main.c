/* Project 1 main entry - video frame encoder */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include "lcgrand.h"
#include "random_gen.h"
#include "queue.h"

extern char *optarg;
extern int optind, opterr, optopt;

/** ================= define global state variable for simulation =================

    float current_sim_time: system simulation clock
    float time_last_event: 
    int buffer_size: encoder buffer size (need to fetch from user input)
    float mean: mean value of simulation (need to fetch from user input)
    (queue.h) frame_frac header: buffer queue of encoder

*/
float mean = 0.1,current_sim_time = 0,total_sim_time = 0.0,time_last_event;
int buffer_size;

/** ================= define individual process function here =================

*/

int main(int argc,char *argv[]){
    /* 
        opt:    getopt usage
        flag:   scheduling type usage
    */
    int opt,flag = 0;
    while((opt = getopt(argc,argv,"b:t:h"))!=-1){
        switch(opt){
            case 'b':
                // buffer size need to plus 1
                buffer_size = atoi(optarg) + 1;
                break;
            case 't':
                total_sim_time = atof(optarg);
                break;
            case 'h':
                fprintf(stdout,
                    "Usage: %s [-t time] [-b buffer]\n\n%s\n%s",
                    argv[0],
                    "-t time:\tspecify the total simulation time (hours)",
                    "-b buffer:\tspecify the buffer size\n"
                    );
                exit(1);
                break;
            default:
                fprintf(stderr,
                    "Usage: %s [-t time] [-b buffer]\n\n%s\n%s",
                    argv[0],
                    "-t time:\tspecify the total simulation time (hours)",
                    "-b buffer:\tspecify the buffer size\n"
                    );
                exit(EXIT_FAILURE);
        }
    }
    printf("Buffer Size=%d\nTotal Simulation time=%f\n",buffer_size,total_sim_time);

    // initialization of queue
    init(buffer_size);
    // create and push the top/bot field
    while(current_sim_time < total_sim_time){
        float t = expon(mean);
        if(get_size() > buffer_size){
            printf("At time: %f, Buffer overflow occurred!\n",current_sim_time);
            break;
        }
        create_and_push(flag,t);
        current_sim_time += t;
        flag = !flag;
    }

    // Get buffer size
    printf("Buffer Size: %d\n",get_size());
    // print for debugging
    print_all();

    return 0;
}
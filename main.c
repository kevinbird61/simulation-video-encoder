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

    --- also need to calculated the result, and source -> to calculate "utilization"
    drop_c:         dropping counter
    drop_filter:   controlling dropping mechanism
    frame_c:        completed frame counter, each of frame contain 2 pieces
*/
float mean = 0.1,current_sim_time = 0,total_sim_time = 0.0,time_last_event=0.0;
int buffer_size,drop_c=0,frame_c=0,drop_filter=-1;

/** ================= define individual process function here =================
    helper:             printing the usage information
    init_simulation:    initialize the simulation routine
    check_buffer:       checking the buffer size, whether it's available or not, then do schedule
    schedule:           base on its type to push event into event queue -> increase queue length, and increase simulation time
*/
void helper(FILE *fp,char *program);
void init_simulation();
int check_buffer();
void schedule(int type); 
void dropping(int type);
void completing();

int main(int argc,char *argv[]){
    fprintf(stdout,
        "\n%s\n%s\n%s\n%s\n\n",
        "Simulation:",
        "Type 1: bottom field",
        "Type 0: top field",
        "==================================="
        );
    /* 
        opt:    getopt usage
        flag:   scheduling type usage
        nums:  how many times we need to run simulation
    */
    int opt,flag = 0,nums=0;
    while((opt = getopt(argc,argv,"n:b:t:h"))!=-1){
        switch(opt){
            case 'n':
                // assign round 
                nums = atoi(optarg);
                break;
            case 'b':
                // buffer size need to plus 1
                buffer_size = atoi(optarg) + 1;
                break;
            case 't':
                total_sim_time = atof(optarg);
                break;
            case 'h':
                helper(stdout,argv[0]);
                exit(1);
                break;
            default:
                helper(stderr,argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    printf("Number of simulation: %d\nBuffer Size=%d\nTotal Simulation time=%f\n",nums,buffer_size,total_sim_time);

    // initialization of queue
    init_simulation();
    // base on event queue to do simulation
    while(current_sim_time < total_sim_time){
        // pop out event from event queue
        frame_frac *e = pop(event_queue);

        switch(e->type){
            case 0:
                // top arrival -> check first, then schedule bot
                if(check_buffer()){
                    // overflow
                    dropping(0);
                }
                else{
                    // push into buffer queue
                    create_and_push(buffer_queue,0,e->timestamp);
                }
                schedule(1);
            break;
            case 1:
                // bot arrival -> check first, then schedule top
                if(check_buffer()){
                    // do nothing
                    dropping(1);
                }
                else{
                    if(drop_filter == 1){
                        // no need to push, set drop_filter back to -1
                        drop_filter = -1;
                    }
                    else{
                        create_and_push(buffer_queue,1,e->timestamp);
                    }
                }
                schedule(0);
                // encode matching top, bot
                schedule(2);
                schedule(3);
            break;
            case 2:
                // encoded top arrival -> do nothing
            break;
            case 3:
                // encoded bot arrival -> do nothing
                // schedule one leaving event -> frame completed
                schedule(4);
            break;
            case 4:
                // need to add up completed frame number
            break;
            case 99:
                // for debugging dummy event, just pass through simulation clock
            break;
            default:
                printf("Invalid event!\n");
        }
        current_sim_time += (float)e->timestamp;
        // Get buffer size
        printf("Event list size: %d\n",get_size(event_queue));
        // print for debugging
        print_all(event_queue);
    }

    // testing: create and push the top/bot field
    /*while(current_sim_time < total_sim_time){
        float t = expon(mean);
        if(get_size(event_queue) > buffer_size){
            printf("At time: %f, Buffer overflow occurred!\n",current_sim_time);
            break;
        }
        create_and_push(event_queue,flag,t);
        current_sim_time += t;
        flag = !flag;
    }*/

    // drop all existed memory usage
    drop_all();

    // create_and_push(event_queue,flag,expon(mean));
    // print_all(event_queue);

    return 0;
}

void schedule(int type){
    float t = expon(mean);
    // need to do increasing size of buffer size/ storage size
    create_and_push(event_queue,type,expon(mean));
}

void dropping(int type){
    // input type is current arrival event during buffer overflow
    switch(type){
        case 0:
            // incoming event is top field, also need to drop its following bot field
            drop_filter = 1; // next time when bot field coming -> drop
        break;
        case 1:
            // incoming event is bot field, need to pop out the buffer queue from the back
            pop_back(buffer_queue);
        break;
        default:
            printf("Invalid dropping type, ignore!");
    }
}
void completing();

int check_buffer(){
    if(get_size(buffer_queue) >= buffer_size){
        return 1;
    }
    return 0;
}

void init_simulation(){
    // initialize the queue usage
    init();
    // reset statistic counter
    current_sim_time=0;
    time_last_event=0;
    drop_c=0;
    frame_c=0;
    // push an top field arrival as starting state
    schedule(0);
    schedule(1);
}

void helper(FILE *fp,char *program){
    fprintf(fp,
        "Usage: %s [-t time] [-b buffer]\n\n%s\n%s\n%s\n",
        program,
        "-n nums:\tspecify how many times you want to run the simulation routine",
        "-t time:\tspecify the total simulation time (hours)",
        "-b buffer:\tspecify the buffer size\n"
        );
}
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
    drop_c:                 dropping counter
    drop_filter:            controlling dropping mechanism
    input_video_pieces:     input video pieces counter
    output_video_pieces:    output video pieces counter
*/
float mean = 0.1,current_sim_time = 0,total_sim_time = 0.0,time_last_event=0.0;
int buffer_size,drop_c=0,frame_c=0,drop_filter=-1,input_video_pieces=0,output_video_pieces=0;

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

int main(int argc,char *argv[]){
    fprintf(stdout,
        "\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
        "Simulation:",
        "Type 1: bottom field",
        "Type 0: top field",
        "Type 2: encoded top field arrival",
        "Type 3: encoded bottom field arrival",
        "Type 4: leaving event",
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
        print_all(event_queue);
        // pop out event from event queue
        frame_frac *e = pop(event_queue);
        // interpret the type of this event
        switch(e->type){
            case 0:
                // top arrival -> check first, then schedule bot
                if(check_buffer()){
                    // overflow
                    dropping(0);
                    // inc 
                    // drop_c++;
                }
                else{
                    // push into buffer queue
                    create_and_push(buffer_queue,0,e->timestamp);
                }
                // Then schedule bot arrival
                schedule(1);
                // inc counter
                input_video_pieces++;
            break;
            case 1:
                // schedule the next top arrival event
                schedule(0);
                // bot arrival -> check first, then schedule top
                if(check_buffer()){
                    // overflow -> pop out the last element in buffer queue
                    dropping(1);
                    // inc 
                    // drop_c++;
                }
                else{
                    // Checking this bot's top is discard or not
                    if(drop_filter == 1){
                        // no need to push, set drop_filter back to -1
                        drop_filter = -1;
                        // inc 
                        // drop_c++;
                    }
                    else{
                        // Its matching top is save
                        create_and_push(buffer_queue,1,e->timestamp);
                        // schedule encode matching top, bot arrival (because available bottom can schedule a pair encoded frame arrival)
                        schedule(2);
                    }
                }
                input_video_pieces++;
            break;
            case 2:
                // encoded top arrival -> push the element in storage server
                push(storage_queue,e);
                schedule(3);
            break;
            case 3:
                // encoded bot arrival -> do nothing
                // schedule one leaving event -> frame completed
                push(storage_queue,e);
                schedule(4);
            break;
            case 4:
                // need to add up completed frame number
                if(get_size(storage_queue) < 2){
                    printf("Invalid leaving event arrival!\n");
                    exit(1);
                }
                else{
                    // FIXME: need to free!
                    // pop(storage_queue);
                    // pop(storage_queue);
                    // add the counter 
                    output_video_pieces += 2;
                }
            break;
            case 99:
                // for debugging dummy event, just pass through simulation clock
            break;
            default:
                printf("Invalid event!\n");
        }
        
        // update current simulation clock
        current_sim_time = (float)e->timestamp;
    }
    printf("Current simulation time: %f;\tTotal simulation time %f\n",current_sim_time,total_sim_time);
    printf("Total arrival pieces(top,bot): %d\n",input_video_pieces);
    printf("Total dropping pieces: %d\n",drop_c);
    printf("Output frame pieces(result top,bot): %d\n",output_video_pieces);
    // free all existed memory usage
    drop_all();
    return 0;
}

void schedule(int type){
    float t = expon(mean);
    // create & push & sort by timestamp
    create_push_sort(event_queue,type,current_sim_time+t);
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
    input_video_pieces=0;
    output_video_pieces=0;
    // push a pair field arrivals as starting state
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
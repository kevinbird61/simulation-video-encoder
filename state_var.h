#ifndef STATE_VAR
#define STATE_VAR

/* Define state variable data type */
#define TOP_SIZE 1
#define BOT_SIZE 2
#define field_size(type) (type==0)?TOP_SIZE:BOT_SIZE;

// determine inter-arrival time
typedef float inter_t;

// frame fraction. 
// 0: top, 1: bottom
typedef struct frame_piece {
    int type;
    int size;
    inter_t timestamp;
    // for link-list
    struct frame_piece *parent;
    struct frame_piece *child;
} frame_frac;

#endif
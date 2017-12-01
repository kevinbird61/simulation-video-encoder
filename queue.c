#include "queue.h"

// initialization
void init(){
    // initialize header
    frame_frac *tmp = (frame_frac*)malloc(sizeof(frame_frac)*1),
        *tmp2 = (frame_frac*)malloc(sizeof(frame_frac)*1),
        *tmp3 = (frame_frac*)malloc(sizeof(frame_frac)*1);
    tmp->parent = NULL;
    tmp2->parent = NULL;
    tmp3->parent = NULL;
    tmp->child = NULL;
    tmp2->child = NULL;
    tmp3->child = NULL;

    // assign header
    event_queue = tmp;
    buffer_queue = tmp2;
    storage_queue = tmp3;
}

// provide creating function for easy usage
int create_and_push(frame_frac *ptr,int type, inter_t timestamp){
    // create new element
    frame_frac *new_ele = (frame_frac*)malloc(sizeof(frame_frac)*1);
    new_ele->type = type;
    // using MACRO 
    new_ele->size = field_size(type);
    new_ele->timestamp = timestamp;
    new_ele->child = NULL;
    new_ele->parent = NULL;

    // push
    push(ptr,new_ele);
    
    return 0;
}

// push new element into queue
int push(frame_frac *ptr,frame_frac *element){
    // ptr is the header we want
    frame_frac *traversal,*parent;
    traversal = ptr;
    while(traversal->child != NULL){
        parent = traversal;
        traversal = traversal->child;
    }
    
    // parent & child
    traversal->parent = parent;
    traversal->child = element;
    return 0;
}

// For the piece which need to go "encoder"
frame_frac *pop(frame_frac *ptr){
    // tmp 
    frame_frac *element;
    // fetch first element
    element = ptr->child;
    // reset header
    ptr->child = element->child;
    element->child->parent = ptr;
    // cut all link, purge element from list
    element->parent=NULL;
    element->child=NULL;
    
    return element;
}

// For the piece which need to be drop out
frame_frac *pop_back(frame_frac *ptr){
    frame_frac *traversal,*parent;
    traversal = ptr;
    while(traversal->child != NULL){
        parent = traversal;
        traversal = traversal->child;
    }
    // cut down
    parent->child = NULL;
    traversal->parent = NULL;
    // pop out traversal
    return traversal;
}

// Print all node from header list
void print_all(frame_frac *ptr){
    frame_frac *traversal;
    traversal = ptr->child;
    while(traversal != NULL){
        print_node(traversal);
        traversal = traversal->child;
    }
}

// Get size of header
int get_size(frame_frac *ptr){
    int size=0;
    frame_frac *traversal;
    traversal = ptr->child;
    while(traversal != NULL){
        traversal = traversal->child;
        size++;
    }
    return size;
}

// Print each node on header list
void print_node(frame_frac *p){
    printf("Type: %s, Size: %d, timestamp: %f\n",(p->type==0)?"top":"bot",p->size,(float)p->timestamp);
}
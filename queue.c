#include "queue.h"

// initialization
void init(){
    // initialize header
    frame_frac *tmp = (frame_frac*)malloc(sizeof(frame_frac)*1);
    tmp->parent = NULL;
    tmp->child = NULL;
    header = tmp;
}

// provide creating function for easy usage
int create_and_push(int type, inter_t timestamp){
    // create new element
    frame_frac *new_ele = (frame_frac*)malloc(sizeof(frame_frac)*1);
    new_ele->type = type;
    // using MACRO 
    new_ele->size = field_size(type);
    new_ele->timestamp = timestamp;
    new_ele->child = NULL;
    new_ele->parent = NULL;

    // push
    push(new_ele);
    
    return 0;
}

// push new element into queue
int push(frame_frac *element){
    frame_frac *traversal,*parent;
    traversal = header;
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
frame_frac *pop(){
    // tmp 
    frame_frac *element;
    // fetch first element
    element = header->child;
    // reset header
    header->child = element->child;
    element->child->parent = header;
    // cut all link, purge element from list
    element->parent=NULL;
    element->child=NULL;
    
    return element;
}

// For the piece which need to be drop out
frame_frac *pop_back(){
    frame_frac *traversal,*parent;
    traversal = header;
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
void print_all(){
    frame_frac *traversal;
    traversal = header->child;
    while(traversal != NULL){
        print_node(traversal);
        traversal = traversal->child;
    }
}

// Get size of header
int get_size(){
    int size=0;
    frame_frac *traversal;
    traversal = header->child;
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
#include "queue.h"

void init(){
    frame_frac *tmp = (frame_frac*)malloc(sizeof(frame_frac)*1);
    tmp->parent = NULL;
    tmp->child = NULL;

    header = tmp;
}

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

// operator
int push(frame_frac *element){
    // malloc header and add the new element on it
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

frame_frac *pop_back(){
    frame_frac *traversal,*parent;
    traversal = header->child;
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

void print_all(){
    frame_frac *traversal;
    traversal = header->child;
    while(traversal->child != NULL){
        print_node(traversal);
        traversal = traversal->child;
    }
}

void print_node(frame_frac *p){
    printf("Type: %d, Size: %d, timestamp: %f\n",p->type,p->size,(float)p->timestamp);
}
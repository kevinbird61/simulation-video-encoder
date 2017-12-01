#include "queue.h"

void init(){
    frame_frac *tmp = malloc(sizeof(frame_frac*)*1);
    tmp->parent = NULL;
    tmp->child = NULL;

    header = tmp;
}

// operator
int push(frame_frac *element){
    // malloc header and add the new element on it
    frame_frac *traversal;
    traversal = header;
    while(traversal->child != NULL)
        traversal = traversal->child;
    
    traversal->child = element;
    return 0;
}

frame_frac *pop(){
    // tmp 
    frame_frac *element;
    // fetch first element
    element = header->child;
    // reset header
    header = header->child;
    header->parent=NULL;
    // cut all link, purge element from list
    element->parent=NULL;
    element->child=NULL;
    
    return element;
}

frame_frac *pop_last(){
    
}

void print_all(){

}
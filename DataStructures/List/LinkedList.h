//
//  LinkedList.h
//  hdelibc
//
//  Created by Eric Meehan on 1/31/21.
//
// The functions that I declared in the header file are accesible by the end user
// of this library. The functions that I declared in the c file are not.
// This is a good way to hide implementation details from the end user.
#ifndef LinkedList_h
#define LinkedList_h

#include <stdlib.h>
#include <stdio.h>
#include "../Common/Node.h"

struct LinkedList
{
    // Head points to the first node in the chain.
    struct Node *head;
    // Length refers to the number of nodes in the chain.
    int length;

    // Insert adds new items to the chain at a specified location - this function creates the new nodes.
    void (*insert)(struct LinkedList *linked_list, int index, void *data, int size);
    // Remove deletes an item from the chain and handles the deallocation of memory.
    void (*remove)(struct LinkedList *linked_list, int index);
    // Retrieve allows data in the chain to be accessed
    void *(*retrieve)(struct LinkedList *linked_list, int index);
};

struct LinkedList linked_list_constructor();
void linked_list_destructor(struct LinkedList *linked_list);

#endif /* LinkedList_h */

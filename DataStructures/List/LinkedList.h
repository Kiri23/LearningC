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

struct LinkedList_int
{
    struct Node_int *head;
    int length;

    void (*insert)(int index, void *data, struct LinkedList_int *linked_list);
    void (*remove)(int index, struct LinkedList_int *linked_list);
    void *(*retrieve)(int index, struct LinkedList_int *linked_list);
};

struct LinkedList_int linked_list_int_constructor();

#endif /* LinkedList_h */

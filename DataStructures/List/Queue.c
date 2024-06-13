//
//  Queue.c
//  hdelibc
//
//  Created by Eric Meehan on 2/3/21.
//

#include "Queue.h"

void push(struct Queue *queue, void *data, int data_type, int size)
{
    // Utilize insert from LinkedList with enforced parameters.
    queue->list.insert(&queue->list, queue->list.length, data, data_type, size);
}

void *peek(struct Queue *queue)
{
    void *data = queue->list.retrieve(&queue->list, 0);
    return data;
}

void pop(struct Queue *queue)
{
    queue->list.remove(&queue->list, 0);
}

struct Queue queue_constructor()
{
    struct Queue queue;
    // here you have the magic of "inherentance" in C
    // by including the linked list header file in the queue header file
    // you can access the linked list functions from the queue functions
    queue.list = linked_list_constructor();

    queue.push = push;
    queue.peek = peek;
    queue.pop = pop;

    return queue;
}

void queue_destructor(struct Queue *queue)
{
    linked_list_destructor(&queue->list);
}

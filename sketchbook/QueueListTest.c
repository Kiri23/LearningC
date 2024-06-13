#include <stdio.h>
#include "../DataStructures/List/Queue.h"

// I will "compile" the test file but will also include the "library" linked list file
//  gcc QueueListTest.c ../DataStructures/List/Queue.c -o ./bin/QueueList
int main()
{
    struct Queue queue = queue_constructor();

    for (int i = 0; i < 10; i++)
    {
        int x[3] = {i, i + 1, i + 3};
        queue.push(&queue, x, Int, sizeof(x));
    }

    queue.pop(&queue);
    queue.pop(&queue);
    queue.pop(&queue);
    int *new_value = (int *)malloc(sizeof(int));
    *new_value = 99;
    queue.push(&queue, new_value, Int, sizeof(new_value));

    // one of the drawback of using OOP is that I can acces the linked list functions from the queue functions
    // so i can manipulate the linked list directly and it will affect the queue
    // queue.list.head = NULL; // this will break the queue

    for (int i = 0; i < 10; i++)
    {
        printf("Node at index %d: %d\n", i, *(int *)queue.peek(&queue));
    }

    // Attempt to retrieve an out-of-bounds index
    // queue.retrieve(100, &queue);

    return 0;
}
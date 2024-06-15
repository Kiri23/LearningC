#include <stdio.h>
#include "../DataStructures/List/Queue.h"

// I will "compile" the test file but will also include the "library" linked list file
//  gcc QueueListTest.c ../DataStructures/List/Queue.c -o ./bin/QueueList
int main()
{
    struct Queue queue = queue_constructor();

    for (int i = 0; i < 10; i++)
    {
        int x[3] = {i, i + 1, i * 2};
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
        void *peeked_value = queue.peek(&queue);
        if (peeked_value != NULL)
        {
            printf("Node at index %d: %d\n", i, *(int *)peeked_value);
        }
        else
        {
            printf("Node at index %d: NULL (queue is empty)\n", i);
        }
        printf("Queue length: %d\n", queue.list.length);
        if (queue.list.length != 0)
        {
            queue.pop(&queue);
        }
    }

    struct Queue queue2 = queue_constructor();
    int x[2] = {10, 5};
    int y[2] = {20, 10};
    printf("segmenation fault\n");
    queue2.push(&queue2, &x, Int, sizeof(int));
    printf("queue2 at x %d: %d\n", 0, *(int *)queue2.peek(&queue2));
    queue2.push(&queue2, &y, Int, sizeof(int));
    printf("queue2 at y %d: %d\n", 1, *(int *)queue2.peek(&queue2));
    queue2.pop(&queue2);
    printf("access violation\n");
    printf("queue2 at index %d: %d\n", 0, *(int *)queue2.peek(&queue2));

    return 0;
}
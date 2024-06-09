#include <stdio.h>
#include "../DataStructures/List/LinkedList.h"

int main()
{
    struct LinkedList_int list = linked_list_int_constructor();

    for (int i = 0; i < 10; i++)
    {
        int *x = (int *)malloc(sizeof(int));
        *x = i;
        list.insert(i, x, &list);
    }

    list.remove(3, &list);
    list.remove(7, &list);
    int *new_value = (int *)malloc(sizeof(int));
    *new_value = 99;
    list.insert(1, new_value, &list);

    for (int i = 0; i < 10; i++)
    {
        printf("Node at index %d: %d\n", i, *(int *)list.retrieve(i, &list));
    }

    // Attempt to retrieve an out-of-bounds index
    list.retrieve(100, &list);

    return 0;
}
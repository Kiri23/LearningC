#include <stdio.h>
#include "../DataStructures/List/LinkedList.h"

int main()
{
    struct LinkedList_int list = linked_list_int_constructor();

    for (int i = 0; i < 10; i++)
    {
        list.insert(i, i, &list);
    }

    list.remove(3, &list);
    list.remove(7, &list);
    list.insert(1, 99, &list);

    for (int i = 0; i < 10; i++)
    {
        printf("Node at index %d: %d\n", i, list.retrieve(i, &list));
    }

    // Attempt to retrieve an out-of-bounds index
    list.retrieve(100, &list);

    return 0;
}
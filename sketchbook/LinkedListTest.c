#include <stdio.h>
#include "../DataStructures/List/LinkedList.h"

// I will "compile" the test file but will also include the "library" linked list file
//  gcc LinkedListTest.c ../DataStructures/List/LinkedList.c ../DataStructures/List/Node.c -o ./bin/LinkedList
int main()
{
    struct LinkedList list = linked_list_constructor();

    for (int i = 0; i < 10; i++)
    {
        int x[10] = {i, i + 2, i + 3, i + 4, i + 5, i + 6, i + 7, i + 8, i + 9, i + 10};
        list.insert(&list, i, x, sizeof(x) / sizeof(int));
    }

    list.remove(&list, 3);
    list.remove(&list, 7);
    // this prove the point that the linked list can have different data types
    char new_value[3] = {'a', 'b', 'c'};
    list.insert(&list, 1, new_value, sizeof(new_value) / sizeof(char));

    for (int i = 0; i < 10; i++)
    {
        void *data = list.retrieve(&list, i);
        if (data != NULL)
        {
            // it caugh me off guard that I have to pass the index of the next element that I want to retrieve
            // the char array is at index 1 but I have to pass 2 because the retrieve function subtracts 1 from the index
            if (i == 2) // Special handling for the char array
            {
                // not sure why I dont get the char code printed out
                char *char_value = (char *)data;
                printf("Node Char at index %d: %d %d %d\n", i, char_value[0], char_value[1], char_value[2]);
                printf("Char array: %s\n", char_value); // Print the entire char array as a string
            }
            else
            {
                int *retrieved_value = (int *)data;
                printf("Node at index %d: %d %d %d %d %d %d %d %d %d %d\n", i,
                       retrieved_value[0], retrieved_value[1], retrieved_value[2],
                       retrieved_value[3], retrieved_value[4], retrieved_value[5],
                       retrieved_value[6], retrieved_value[7], retrieved_value[8],
                       retrieved_value[9]);
            }
        }
        else
        {
            printf("Node at index %d: NULL\n", i);
        }
    }

    printf("Attempting to retrieve an out-of-bounds index...\n");
    // Attempt to retrieve an out-of-bounds index
    list.retrieve(&list, 100);

    return 0;
}
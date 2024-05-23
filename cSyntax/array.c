#include <stdio.h>

int main()
{
    int arr[10000]; // create an array of 10 integers
    arr[3] = 2;     // set the 4th element to 2

    // Print the memory address of each element in the array
    for (int i = 0; i < 10; i++)
    {
        printf("arr[%d] is at address %p with value %d\n", i, (void *)&arr[i], arr[i]);
    }

    printf("Memory used by arr: %lu bytes\n", sizeof(arr)); // 4 * 10 bytes
    return 0;
}
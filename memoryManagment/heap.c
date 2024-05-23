#include <stdio.h>

int main() {
    // Trying to allocate a very large array on the stack
    char large_array[30000000000];
    
    // This line is unlikely to be reached due to the stack overflow
    printf("Array allocated.\n");

    return 0;
}

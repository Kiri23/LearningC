#include <stdio.h>
#include "../DataStructures/Trees/BinarySearchTree.h"
// Run with gcc BinarySearchTreeTest.c -o bin/BinarySearchTreeTest ../hdelibc.a

int compare_int(void *a, void *b)
{
    printf("Comparing...\n");
    int int_a = *((int *)a);
    int int_b = *((int *)b);
    printf("int_a: %d\n", int_a);
    printf("int_b: %d\n", int_b);

    if (int_a < int_b)
    {
        return -1;
    }
    else if (int_a == int_b)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int main()
{
    struct BinarySearchTree tree = binary_search_tree_constructor(compare_int);

    // Insert some integers into the tree
    int data1 = 5;
    int data2 = 3;
    int data3 = 7;
    int data4 = 2;
    int data5 = 4;
    int data6 = 6;
    int data7 = 8;

    tree.insert(&tree, &data1, sizeof(int));
    tree.insert(&tree, &data2, sizeof(int));
    tree.insert(&tree, &data3, sizeof(int));
    tree.insert(&tree, &data4, sizeof(int));
    tree.insert(&tree, &data5, sizeof(int));
    tree.insert(&tree, &data6, sizeof(int));
    tree.insert(&tree, &data7, sizeof(int));

    // // Search for some integers in the tree
    int search_data1 = 5;
    int search_data2 = 10;

    int *result1 = (int *)tree.search(&tree, &search_data1);
    int *result2 = (int *)tree.search(&tree, &search_data2);

    if (result1 != NULL)
    {
        printf("Found %d in the tree.\n", *result1);
    }
    else
    {
        printf("%d is not in the tree.\n", search_data1);
    }

    return 0;
}
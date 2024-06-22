//
//  BinarySearchTree.h
//  hdelibc
//
//  Created by Eric Meehan on 2/11/21.
//
/*
 The BinarySearch tree struct is a collection of Nodes, each containing pointers to no more than two children.
 Children with data values less than the parent are stored to the left (previous), and those with values grater than the parent are stored to the right (next).
 Since the data type of the Nodes is unknown, users must specify their own comparison function for the tree in its constructor.
 Note that these functions should compare the stored data - not the Nodes themselves.
 */
#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include "../Common/Node.h"

struct BinarySearchTree
{
    struct Node *head;

    int (*compare)(void *data_one, void *data_two);
    void *(*search)(struct BinarySearchTree *tree, void *data);
    void (*insert)(struct BinarySearchTree *tree, void *data, int size);
};

struct BinarySearchTree binary_search_tree_constructor(int (*compare)(void *data_one, void *data_two));

#endif /* BinarySearchTree_h */
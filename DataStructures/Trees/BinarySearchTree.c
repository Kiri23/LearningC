//
//  BinarySearchTree.c
//  hdelibc
//
//  Created by Eric Meehan on 2/11/21.
//

#include "BinarySearchTree.h"

struct Node *create_node_bst(void *data, int size);
void destroy_node_bst(struct Node *node_to_destroy);

void *search_bst(struct BinarySearchTree *tree, void *data);
void insert_bst(struct BinarySearchTree *tree, void *data, int size);

struct BinarySearchTree binary_search_tree_constructor(int (*compare)(void *data_one, void *data_two))
{
    struct BinarySearchTree tree;
    tree.compare = compare;
    tree.search = search_bst;
    tree.insert = insert_bst;
    return tree;
}

struct Node *create_node_bst(void *data, int size)
{
    // Allocate space.
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    // Call the constructor.
    *new_node = node_constructor(data, size);
    return new_node;
}

// The destroy_node_bst function removes a node by deallocating it's memory address.  This simply renames the node destructor function.
void destroy_node_bst(struct Node *node_to_destroy)
{
    node_destructor(node_to_destroy);
}

/** Returning two values mutating the direction and returning the node (cursor) where the list end */
struct Node *iterate_bst(struct BinarySearchTree *tree, struct Node *cursor, void *data, int *direction)
{
    int comparison = tree->compare(cursor->data, data);
    if (comparison == 1)
    {
        // keep traversing the tree to the right
        if (cursor->next)
        {
            return iterate_bst(tree, cursor->next, data, direction);
        }
        else
        {
            *direction = 1;
            return cursor;
        }
    }
    else if (comparison == -1)
    {
        if (cursor->previous)
        {
            return iterate_bst(tree, cursor->previous, data, direction);
        }
        else
        {
            *direction = -1;
            return cursor;
        }
    }
    else
    {
        *direction = 0;
        return cursor;
    }
}

void *search_bst(struct BinarySearchTree *tree, void *data)
{
    // si pong int direction = null; causa error de segmentation pq
    // null no es un valor valido para un int
    int direction = 0;
    struct Node *cursor = iterate_bst(tree, tree->head, data, &direction);
    if (direction == 0)
    {
        return cursor->data;
    }
    else
    {
        return NULL;
    }
}

void insert_bst(struct BinarySearchTree *tree, void *data, int size)
{
    int direction = 0;
    if (tree == NULL)
    {
        printf("Tree is null...\n");
    }
    if (tree->head == NULL)
    {
        printf("Creating head...\n");
        tree->head = create_node_bst(data, size);
        return;
    }
    struct Node *cursor = iterate_bst(tree, tree->head, data, &direction);
    if (direction == 1)
    {
        // derecha -> mayor que
        cursor->next = create_node_bst(data, size);
    }
    else if (direction == -1)
    {
        // izquierda -> menor que
        cursor->previous = create_node_bst(data, size);
    }
    else
    {
        printf("Data already exists in the tree...\n");
    }
}
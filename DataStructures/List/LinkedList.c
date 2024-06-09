//
//  LinkedList.c
//  hdelibc
//
//  Created by Eric Meehan on 1/31/21.
//

#include "LinkedList.h"

struct Node *create_node(void *data);
void destroy_node(struct Node *node_to_destroy);

struct Node *iterate(int index, struct LinkedList *linked_list);
void insert_node(int index, void *data, struct LinkedList *linked_list);
void remove_node(int index, struct LinkedList *linked_list);
void *retrieve_data(int index, struct LinkedList *linked_list);

struct LinkedList linked_list_constructor()
{
    struct LinkedList new_list;
    new_list.head = NULL;
    new_list.length = 0;

    new_list.insert = insert_node;
    new_list.remove = remove_node;
    new_list.retrieve = retrieve_data;

    return new_list;
}

struct Node *create_node(void *data)
{
    // this is what calling the "new" keyword (new Node) do under the hood
    struct Node *new_node_address = (struct Node *)malloc(sizeof(struct Node));
    struct Node new_node_instance;
    new_node_instance.data = data;
    new_node_instance.next = NULL;
    // the * dereferences the pointer. meaning it gets the value at the address
    // which in this case there is a type match because the address is a pointer to a Node
    *new_node_address = new_node_instance;
    return new_node_address;
}

void destroy_node(struct Node *node_to_destroy)
{
    free(node_to_destroy->data);
    free(node_to_destroy);
}

struct Node *iterate(int index, struct LinkedList *linked_list)
{
    if (index < 0 || index >= linked_list->length)
    {
        printf("Index out of bound..");
        exit(9);
    }
    struct Node *cursor = linked_list->head;
    for (int i = 0; i < index; i++)
    {
        cursor = cursor->next;
    }
    return cursor;
}

void insert_node(int index, void *data, struct LinkedList *linked_list)
{
    struct Node *node_to_insert = create_node(data);

    if (index == 0)
    {
        node_to_insert->next = linked_list->head;
        linked_list->head = node_to_insert;
    }
    else
    {
        struct Node *cursor = iterate(index - 1, linked_list);
        node_to_insert->next = cursor->next;
        cursor->next = node_to_insert;
    }
    linked_list->length += 1;
}

void remove_node(int index, struct LinkedList *linked_list)
{
    if (linked_list->head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    if (index == 0)
    {
        struct Node *node_to_remove = linked_list->head;
        linked_list->head = node_to_remove->next;
        destroy_node(node_to_remove);
    }
    else
    {
        struct Node *cursor = iterate(index - 1, linked_list);
        struct Node *node_to_remove = cursor->next;
        cursor->next = node_to_remove->next;
        destroy_node(node_to_remove);
    }
    linked_list->length -= 1;
}

void *retrieve_data(int index, struct LinkedList *linked_list)
{
    struct Node *cursor = iterate(index, linked_list);
    return cursor->data;
}

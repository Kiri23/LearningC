//
//  Dictionary.c
//  hdelibc
//
//  Created by Eric Meehan on 2/12/21.
//

#include "Dictionary.h"
#include <stdlib.h>

#include <stdio.h>

// Insert adds items to the dictionary - the user does not need to implement Elements themselves.
void insert(struct Dictionary *dictionary, void *key, int key_size, void *value, int value_size);
// Search finds the value for a given key in the Dictionary.
void *search_dict(struct Dictionary *dictionary, void *key, int key_size);

struct Dictionary dictionary_constructor(int (*compare)(void *key_one, void *key_two))
{
    struct Dictionary dictionary;
    dictionary.binary_search_tree = binary_search_tree_constructor(compare);
    dictionary.insert = insert;
    dictionary.search = search_dict;
    return dictionary;
}

void *search_dict(struct Dictionary *dictionary, void *key, int key_size)
{
    // Why this dummy value?
    // int dummy_value = 0;
    // struct Entry searchable = entry_constructor(key, key_size, &dummy_value, sizeof(dummy_value));

    // Use the iterate function of the BinarySearchTree to find the desired element.
    void *result = dictionary->binary_search_tree.search(&dictionary->binary_search_tree, key);
    // Return either the value for that key or NULL if not found.
    if (result)
    {
        return ((struct Entry *)result)->value;
    }
    else
    {
        return NULL;
    }
}

void insert(struct Dictionary *dictionary, void *key, int key_size, void *value, int value_size)
{
    // Create a new Entry.
    struct Entry entry = entry_constructor(key, key_size, value, value_size);
    // Insert that entry into the tree.
    dictionary->binary_search_tree.insert(&dictionary->binary_search_tree, &entry, sizeof(entry));
}
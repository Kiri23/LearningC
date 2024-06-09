//
//  Node.h
//  hdelibc
//
//  Created by Eric Meehan on 1/31/21.
//
// https://github.com/ericomeehan/libeom/commits/615bf5dc755c57d2097ac790ee6ef464c28fc3f9/DataStructures/Node.c?browsing_rename_history=true&new_path=DataStructures/Lists/LinkedList.c&original_branch=main
// git clone
// git checkout 615bf5dc755c57d2097ac790ee6ef464c28fc3f9
// rm -rf .git
#ifndef Node_h
#define Node_h

struct Node_int
{
    int data;
    struct Node_int *next;
};

#endif /* Node_h */

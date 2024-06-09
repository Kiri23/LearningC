//
//  Node.h
//  hdelibc
//
//  Created by Eric Meehan on 1/31/21.
// Use the link below to get the code for a given video
// https://github.com/ericomeehan/libeom/commits/615bf5dc755c57d2097ac790ee6ef464c28fc3f9/DataStructures/Node.c?browsing_rename_history=true&new_path=DataStructures/Lists/LinkedList.c&original_branch=main
// git clone
// git checkout 615bf5dc755c57d2097ac790ee6ef464c28fc3f9
// rm -rf .git
#ifndef Node_h
#define Node_h

struct Node
{
    void *data;
    struct Node *next;
};

#endif /* Node_h */

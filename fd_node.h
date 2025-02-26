#ifndef FD_NODE_H
#define FD_NODE_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>


// Linked List data structure for the FDs
typedef struct fd_node {
    int fd;
    char* file_name;
    long vnode;
    int size;
    struct fd_node* next;
} FDNode;

// Creates a FD Node
FDNode* create_fd(int fd, char* file_name, long vnode);

// Frees all nodes in a FD Linked List
void free_fds(FDNode* fds);

// Gets the FDs of a process with given PID
FDNode* get_fds(int pid);

#endif
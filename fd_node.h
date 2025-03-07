#ifndef FD_NODE_H
#define FD_NODE_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

// Define a macro for the max length of a filename
#define FILENAME_LENGTH 1024

// Linked List data structure for the FDs
typedef struct fd_node {
    int fd;
    char filename[FILENAME_LENGTH];
    long vnode;
    int size;
    struct fd_node* next;
} FDNode;

// Creates a FD Node
FDNode* create_fd(int fd, char* filename, long vnode);

// Frees all nodes in a FD Linked List
void free_fds(FDNode* fds);

// Gets the FDs of a process with given PID
FDNode* get_fds(int pid);

void get_filename(char* path, char* filename, int length);

#endif
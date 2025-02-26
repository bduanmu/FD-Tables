#ifndef PROCESS_NODE_H
#define PROCESS_NODE_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>

#include "fd_node.h"


// Linked List data structure for the processes
typedef struct process_node {
    int pid;
    FDNode* fds;
    struct process_node* next;
} ProcessNode;

// Creates a Process Node
ProcessNode* create_process(int pid, FDNode* fds);

// Frees all nodes in a Process Linked List
void free_processes(ProcessNode* processes);

// Gets the PIDs of current processes and stores them in pids
ProcessNode* get_processes();

#endif
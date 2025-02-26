#include "fd_node.h"

// Creates a FD Node
FDNode* create_fd(int fd, char* file_name, long vnode) {
    FDNode* fd_node = (FDNode*)malloc(sizeof(FDNode));
    fd_node->fd = fd;
    fd_node->file_name = file_name;
    fd_node->vnode = vnode;
    fd_node->size = 1;
    fd_node->next = NULL;

    return fd_node;
}

 // Frees all nodes in a FD Linked List
void free_fds(FDNode* fds) {
    FDNode* temp;
    while (fds) {
        temp = fds;
        fds = fds->next;
        free(temp);
    }
}

// Gets the FDs of a process with given PID
FDNode* get_fds(int pid) {
    return NULL;
}
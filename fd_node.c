#define _POSIX_C_SOURCE 200112L

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
    // Opening the process directory for the given PID to find the FDs
    char dir_address[100];
    sprintf(dir_address, "/proc/%d/fd", pid);
    DIR* fd_dir = opendir(dir_address);

    // If there is an issue with opening /proc, output an error
    if (!fd_dir) {
        fprintf(stderr, "Error opening /proc/%d/fd.\n", pid);
        exit(EXIT_FAILURE);
    }

    // Processing each entry for a process
    struct dirent* entry;
    FDNode* head = NULL;
    FDNode* tail = NULL;
    while ((entry = readdir(fd_dir))) {
        // If entry is a FD, add to fds
        if (isdigit(entry->d_name[0])) {
            // Getting the FD
            int fd = atoi(entry->d_name);

            // Creating a new Process Node
            FDNode* process = create_fd(fd, entry->d_name, -1); // TODO: Add filename and vnode count
            
            // Appending to the list of processes
            if (!tail) {
                head = process;
                tail = process;
            } else {
                tail->next = process;
                tail = process;
            }
        }
    }

    // Closing /proc
    closedir(fd_dir);

    return head;
}
#define _POSIX_C_SOURCE 200112L

#include "fd_node.h"

// Creates a FD Node
FDNode* create_fd(int fd, char* filename, long vnode) {
    FDNode* fd_node = (FDNode*)malloc(sizeof(FDNode));
    fd_node->fd = fd;
    strncpy(fd_node->filename, filename, FILENAME_LENGTH);
    fd_node->vnode = vnode;
    fd_node->size = 1;
    fd_node->next = NULL;

    return fd_node;
}

 // Frees all nodes in a FD Linked List
void free_fds(FDNode* fds) {
    // Looping through each FD node and individually frees them
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

    // If we cannot access the FDs of a certain process, return NULL
    if (!fd_dir) {
        // Closing /proc
        closedir(fd_dir);

        // Return NULL
        return NULL;
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

            // Getting the filename
            char filename[FILENAME_LENGTH];
            char path[100];
            sprintf(path, "/proc/%d/fd/%d", pid, fd);
            get_filename(path, filename, FILENAME_LENGTH);

            // Getting the Vnode
            long vnode = entry->d_ino;
            

            // Creating a new FD Node
            FDNode* fd_node = create_fd(fd, filename, vnode);
            
            // Appending to the list of processes
            if (!tail) {
                head = fd_node;
                tail = fd_node;
            } else {
                head->size++;
                tail->next = fd_node;
                tail = fd_node;
            }
        }
    }

    // Closing /proc
    closedir(fd_dir);

    return head;
}

// Gets the filename from a symlink
void get_filename(char* path, char* filename, int length) {
    // Read the symlink at the path provided
    int len = readlink(path, filename, length - 1);

    // If failed to read link, output an error
    if (len == -1) {
        strcpy(filename, "Filename Unavailable");
    } else {
        // Ending the filename in the proper place
        filename[len] = '\0';
    }
}

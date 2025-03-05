#include "output_utils.h"

// Outputs the composite table
void print_composite(ProcessNode* processes, FILE* stream) {
    // Print the header
    fprintf(stream, "\tPID\tFD\tFilename\t\tInode\n");
    fprintf(stream, "\t================================================\n");

    // Count the line number
    int i = 0;

    // Loop through every process and every FD
    while (processes) {
        FDNode* fds = processes->fds;
        while (fds) {
            fprintf(stream, "%d\t%d\t%d\t%-20s    %ld\n", i, processes->pid, fds->fd, fds->filename, fds->vnode);
            fds = fds->next;

            i++;
        }
        processes = processes->next;
    }
}
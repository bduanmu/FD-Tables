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
    
    fprintf(stream, "\t================================================\n\n");
}

// Outputs the composite table with less formatting
void print_composite_less(ProcessNode* processes, FILE* stream) {
    // Loop through every process and every FD
    while (processes) {
        FDNode* fds = processes->fds;
        while (fds) {
            fprintf(stream, "%d\t%d\t%s\t%ld\n", processes->pid, fds->fd, fds->filename, fds->vnode);
            fds = fds->next;
        }
        processes = processes->next;
    }
}

// Outputs the composite table with less formatting in binary
void print_composite_less_bin(ProcessNode* processes, FILE* stream) {
    char separator[1] = "\t";
    char end[1] = "\n";

    // Loop through every process and every FD
    while (processes) {
        FDNode* fds = processes->fds;
        while (fds) {
            fwrite(&processes->pid, sizeof(int), 1, stream);
            fwrite(separator, sizeof(char), 1, stream);
            fwrite(&fds->fd, sizeof(int), 1, stream);
            fwrite(separator, sizeof(char), 1, stream);
            fwrite(fds->filename, sizeof(char), strlen(fds->filename), stream);
            fwrite(separator, sizeof(char), 1, stream);
            fwrite(&fds->vnode, sizeof(long), 1, stream);
            fwrite(end, sizeof(char), 1, stream);

            fds = fds->next;
        }
        processes = processes->next;
    }
}

// Outputs the table with only the processes and FDs
void print_process_table(ProcessNode* processes, FILE* stream) {
    // Print the header
    fprintf(stream, "\tPID\tFD\n");
    fprintf(stream, "\t=============\n");

    // Count the line number
    int i = 0;

    // Loop through every process and every FD
    while (processes) {
        FDNode* fds = processes->fds;
        while (fds) {
            fprintf(stream, "%d\t%d\t%d\n", i, processes->pid, fds->fd);
            fds = fds->next;

            i++;
        }
        processes = processes->next;
    }
    
    fprintf(stream, "\t=============\n\n");
}

// Outputs the table with only the processes, FDs, and filenames
void print_system_wide_table(ProcessNode* processes, FILE* stream) {
    // Print the header
    fprintf(stream, "\tPID\tFD\tFilename\n");
    fprintf(stream, "\t===============================\n");

    // Count the line number
    int i = 0;

    // Loop through every process and every FD
    while (processes) {
        FDNode* fds = processes->fds;
        while (fds) {
            fprintf(stream, "%d\t%d\t%d\t%s\n", i, processes->pid, fds->fd, fds->filename);
            fds = fds->next;

            i++;
        }
        processes = processes->next;
    }
    
    fprintf(stream, "\t===============================\n\n");
}

// Outputs the table with only the Inodes
void print_vnodes_table(ProcessNode* processes, FILE* stream) {
    // Print the header
    fprintf(stream, "\tInode\n");
    fprintf(stream, "\t========\n");

    // Count the line number
    int i = 0;

    // Loop through every process and every FD
    while (processes) {
        FDNode* fds = processes->fds;
        while (fds) {
            fprintf(stream, "%d\t%ld\n", i, fds->vnode);
            fds = fds->next;

            i++;
        }
        processes = processes->next;
    }
    
    fprintf(stream, "\t========\n\n");
}

// Outputs the summary table
void print_summary(ProcessNode* processes, FILE* stream) {
    // Print the header
    fprintf(stream, "Summary Table\n");
    fprintf(stream, "================\n");

    // Loop through every process and find the number of FDs
    while (processes) {
        fprintf(stream, "%d (%d), ", processes->pid, processes->fds->size);

        processes = processes->next;
    }
    
    fprintf(stream, "\n================\n\n");
}

// Outputs the offending processes
void print_offending(ProcessNode* processes, FILE* stream, int threshold) {
    // Print the header
    fprintf(stream, "## Offending processes -- #FD threshold = %d\n", threshold);

    // Loop through every process and find offending processes
    while (processes) {
        if (processes->fds->size > threshold) {
            fprintf(stream, "%d (%d), ", processes->pid, processes->fds->size);
        }

        processes = processes->next;
    }
    
    fprintf(stream, "\n\n");
}
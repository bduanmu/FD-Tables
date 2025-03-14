#include "process_node.h"

// Creates a ProcessNode
ProcessNode* create_process(int pid, FDNode* fds) {
    ProcessNode* process = (ProcessNode*)malloc(sizeof(ProcessNode));
    process->pid = pid;
    process->fds = fds;
    process->next = NULL;

    return process;
}

// Frees all nodes in a Process Linked List
void free_processes(ProcessNode* processes) {
    // Looping through each process node and individually frees them
    ProcessNode* temp;
    while (processes) {
        temp = processes;
        processes = processes->next;
        free_fds(temp->fds); // Freeing the stored FDs
        free(temp);
    }
}

// Gets current processes and their information
ProcessNode* get_processes() {
    // Opening the /proc directory to find the processes
    DIR* proc_dir = opendir("/proc");

    // If there is an issue with opening /proc, output an error
    if (!proc_dir) {
        perror("Error opening /proc.\n");
        exit(EXIT_FAILURE);
    }

    // Processing each entry for a process
    struct dirent* entry;
    ProcessNode* head = NULL;
    ProcessNode* tail = NULL;
    while ((entry = readdir(proc_dir))) {
        // If entry is a process, add to pids
        if (isdigit(entry->d_name[0])) {
            // Getting the PID
            int pid = atoi(entry->d_name);

            // Finding the FDs
            FDNode* fds = get_fds(pid);

            // If a process's FDs cannot be accessed, ignore it
            if (!fds) continue;

            // Creating a new Process Node
            ProcessNode* process = create_process(pid, fds);
            
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
    closedir(proc_dir);

    return head;
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>


// CDT which holds the program specifications
typedef struct tool_specifications {
    bool show_process;
    bool show_system_wide;
    bool show_vnodes;
    bool show_composite;
    bool show_summary;
    bool save_to_txt_file;
    bool save_to_bin_file;
    int threshold; // Value of -1 if there is no threshold
    int target_pid; // Value of -1 if there is no target PID
} ToolSpecifications;

// Linked List data structure for the processes
typedef struct process_node {
    int pid;
    struct process_node* next;
} ProcessNode;


// Creates a ProcessNode
ProcessNode* create_process(int pid) {
    ProcessNode* process = (ProcessNode*)malloc(sizeof(ProcessNode));
    process->pid = pid;
    process->next = NULL;

    return process;
}

// Frees all nodes in a Process Linked List
void free_processes(ProcessNode* processes) {
    ProcessNode* temp;
    while (processes) {
        temp = processes;
        processes = processes->next;
        free(temp);
    }
}

// Processes the command line arguments
ToolSpecifications* process_arguments(int argc, char* argv[]) {
    // Defining the specifications structure with default values.
    ToolSpecifications* specs = (ToolSpecifications*)malloc(sizeof(ToolSpecifications));
    specs->show_process = false;
    specs->show_system_wide = false;
    specs->show_vnodes = false;
    specs->show_composite = false;
    specs->show_summary = false;
    specs->save_to_txt_file = false;
    specs->save_to_bin_file = false;
    specs->threshold = -1;
    specs->target_pid = -1;

    // Checking for flags
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--per-process") == 0) specs->show_process = true;
        else if (strcmp(argv[i], "--systemWide") == 0) specs->show_system_wide = true;
        else if (strcmp(argv[i], "--Vnodes") == 0) specs->show_vnodes = true;
        else if (strcmp(argv[i], "--composite") == 0) specs->show_composite = true;
        else if (strcmp(argv[i], "--summary") == 0) specs->show_summary = true;
        else if (strcmp(argv[i], "--output_TXT") == 0) specs->save_to_txt_file = true;
        else if (strcmp(argv[i], "--output_binary") == 0) specs->save_to_bin_file = true;
        else if (strncmp(argv[i], "--threshold=", 12) == 0) 
            specs->threshold = atoi(argv[i] + 12) > 0 ? atoi(argv[i] + 12) : -1;
        else if (i == 1) specs->target_pid = atoi(argv[i]) > 0 ? atoi(argv[i]) : -1;
    }

    // No show table flags are passed, display the composite table
    if (!specs->show_process && !specs->show_system_wide && !specs->show_vnodes && 
        !specs->show_composite && !specs->show_summary) {
        specs->show_composite = true;
    }

    // Return the processed specifications
    return specs;
}

// Gets the PIDs of current processes and stores them in pids
ProcessNode* get_pids() {
    // Opening the /proc directory to find the processes
    DIR* proc_dir = opendir("/proc");

    // If there is an issue with opening /proc, output an error
    if (!proc_dir) {
        perror("Error opening /proc.");
        exit(EXIT_FAILURE);
    }

    // Processing each entry for a process
    struct dirent* entry;
    ProcessNode* head = NULL;
    while ((entry = readdir(proc_dir))) {
        // If entry is a process, add to pids
        if (isdigit(entry->d_name[0])) {
            ProcessNode* process = create_process(atoi(entry->d_name));
            process->next = head;
            head = process;
        }
    }

    // Closing /proc
    closedir(proc_dir);

    return head;
}

int main(int argc, char* argv[]) {
    // Processing the arguments
    ToolSpecifications* specs = process_arguments(argc, argv);

    ProcessNode* processes = get_pids();
    while (processes) {
        printf("%d\n", processes->pid);
        processes = processes->next;
    }

    free_processes(processes);
    free(specs);

    exit(EXIT_SUCCESS);
}
#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

#include "process_node.h"
#include "output_utils.h"


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

int main(int argc, char* argv[]) {
    // Processing the arguments
    ToolSpecifications* specs = process_arguments(argc, argv);

    // Retrieving data
    ProcessNode* processes = get_processes();

    // Outputting data
    print_composite(processes, stdout);

    // Freeing data structures
    free_processes(processes);
    free(specs);

    exit(EXIT_SUCCESS);
}
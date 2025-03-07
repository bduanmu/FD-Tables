#ifndef OUTPUT_UTILS_H
#define OUTPUT_UTILS_H

#include <stdlib.h>
#include <stdio.h>

#include "process_node.h"


// Outputs the composite table
void print_composite(ProcessNode* processes, FILE* stream);

// Outputs the composite table with less formatting
void print_composite_less(ProcessNode* processes, FILE* stream);

// Outputs the composite table in binary
void print_composite_less_bin(ProcessNode* processes, FILE* stream);

// Outputs the table with only the processes and FDs
void print_process_table(ProcessNode* processes, FILE* stream);

// Outputs the table with only the processes, FDs, and filenames
void print_system_wide_table(ProcessNode* processes, FILE* stream);

// Outputs the table with only the Inodes
void print_vnodes_table(ProcessNode* processes, FILE* stream);

// Outputs the summary table
void print_summary(ProcessNode* processes, FILE* stream);

// Outputs the offending processes
void print_offending(ProcessNode* processes, FILE* stream, int threshold);

#endif
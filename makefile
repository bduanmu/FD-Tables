# Compiler
CC = gcc
# Compiler Flags
CFLAGS = -Wall -Werror -std=c99 -g
# Output executable
TARGET = fd_tables
# Source files
SRC = fd_tables.c process_node.c fd_node.c output_utils.c
# Object files
OBJ = $(SRC:.c=.o)
# Header files
DEPS = process_node.h fd_node.h output_utils.h

# Default rule to build the executable
all: $(TARGET)

# Compile object files
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the object files into the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Clean rule to remove compiled files
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all clean
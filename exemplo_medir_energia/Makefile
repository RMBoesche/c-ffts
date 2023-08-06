# Makefile for compiling the C program

# Compiler
CC = gcc

# Compiler flags for the default target and "o1"
CFLAGS = -Wall -Wextra -Wpedantic

# Compiler flags for "o2"
CFLAGS_O2 = -O2

# Compiler flags for "o3"
CFLAGS_O3 = -O3

# Source files
SRCS = exemplo.c energia.c ../c-fft/fft.c ../c-fft/complex.c

# Object files
OBJS = $(SRCS:.c=.o)

# Output executables
TARGET = test
TARGET_O1 = test_o1
TARGET_O2 = test_o2
TARGET_O3 = test_o3

# Libraries
LIBS = -lm

# Default target (all) - will build the executable
all: $(TARGET)

# Rule to build the executable with default flags
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

# Rule to build the executable with "-O1" optimization flag
o1: CFLAGS += $(CFLAGS_O1)
o1: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET_O1)

# Rule to build the executable with "-O2" optimization flag
o2: CFLAGS += $(CFLAGS_O2)
o2: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET_O2)

# Rule to build the executable with "-O3" optimization flag
o3: CFLAGS += $(CFLAGS_O3)
o3: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET_O3)

# Rule to build object files from source files
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target - removes all generated files
clean:
	rm -f $(OBJS) $(TARGET) $(TARGET_O1) $(TARGET_O2) $(TARGET_O3)

# Phony targets - targets that are not real files
.PHONY: all o1 o2 o3 clean


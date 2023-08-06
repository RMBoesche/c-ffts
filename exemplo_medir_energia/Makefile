# Makefile for compiling the C program

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Wpedantic

# Source files
SRCS = exemplo.c energia.c ../c-fft/fft.c ../c-fft/complex.c

# Object files
OBJS = $(SRCS:.c=.o)

# Output executable name
TARGET = test

# Libraries
LIBS = -lm

# Default target (all) - will build the executable
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET) -O2

# Rule to build object files from source files
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target - removes all generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets - targets that are not real files
.PHONY: all clean


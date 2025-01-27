# ----------------------------------------
# Makefile for CP264 Lab 01
# Author: [Your Name]
# Student Number: [Your Student Number]
# 
# Usage:
#   make        - builds the program
#   make clean  - removes build files
#   make run    - builds and runs the program
#   make debug  - builds with debug symbols
#   make lldb   - starts LLDB debugger
# ----------------------------------------
# Directory Structure:
#   src/     - source files
#   include/ - header files
#   bin/     - output executables
#   build/   - object files
# ----------------------------------------

# Compiler and flags
CC = gcc
CFLAGS = -I./include
DEBUGFLAGS = -g

# Directories
SRCDIR = src
BINDIR = bin
BUILDDIR = build

# Target executable
TARGET = $(BINDIR)/Maso2187_l03

# ----------------------------------------
# Build Configuration:
# - Uses gcc compiler
# - Automatically finds all .c files in src/
# - Creates corresponding .o files in build/
# - Links into final executable in bin/
# ----------------------------------------

# Source and object files
# SOURCES = $(SRCDIR)/main.c $(SRCDIR)/parameters.c
# OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

# Default target
all: $(BINDIR) $(BUILDDIR) $(TARGET)

# Create directories if they don't exist
$(BINDIR):
	mkdir -p $(BINDIR)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Link the program
$(TARGET): $(OBJECTS)
	@echo "Linking program: $(TARGET)"
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compiling: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	@echo "Cleaning build files..."
	rm -rf $(BUILDDIR)
	rm -rf $(BINDIR)
	@echo "Cleaned!"
	
# Run the program
run: $(TARGET)
	@echo "Running program..."
	@./$(TARGET)

# Debug build
debug: CFLAGS += $(DEBUGFLAGS)
debug: clean
	@$(MAKE) all
	@echo "Built with debug information"

# Start debugger (using LLDB for macOS)
lldb: debug
	@echo "Starting LLDB debugger..."
	@lldb $(TARGET)

.PHONY: all clean run debug lldb

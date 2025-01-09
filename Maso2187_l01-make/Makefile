# Compiler and flags
CC = gcc
CFLAGS = -I./include

# Directories
SRCDIR = src
BINDIR = bin
BUILDDIR = build

# Target executable
TARGET = $(BINDIR)/Maso2187_l01

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

.PHONY: all clean

# Compiler settings
CC = cc
CFLAGS = 

# Directories
SRC_DIR = src
BIN_DIR = bin

# Ensure bin directory exists
$(shell mkdir -p $(BIN_DIR))

# Targets
all: q1 q2 q3

# Q1: Queue
q1: | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(SRC_DIR)/hash.c $(SRC_DIR)/hash_ptest.c

# Q2: Stack
q2: | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(SRC_DIR)/expression_symbol.c $(SRC_DIR)/common_queue_stack.c $(SRC_DIR)/hash.c $(SRC_DIR)/expression_symbol_ptest.c

# Q3: Expression
q3: | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(SRC_DIR)/heap.c $(SRC_DIR)/heap_ptest.c

# Create zip file for submission
zip:
	cd $(SRC_DIR) && zip ../a8.zip *

# Clean rule
clean:
	rm -f $(BIN_DIR)/*

# Phony targets
.PHONY: all clean q1 q2 q3 zip

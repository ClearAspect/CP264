# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra

# Directories
SRC_DIR = src
BIN_DIR = bin

# Ensure bin directory exists
$(shell mkdir -p $(BIN_DIR))

# Targets
all: q1 q2 q3

# Q1: Single Linked List
q1: | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(SRC_DIR)/myrecord_sllist.c $(SRC_DIR)/myrecord_sllist_ptest.c

# Q2: Double Linked List
q2: | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(SRC_DIR)/dllist.c $(SRC_DIR)/dllist_ptest.c

# Q3: Stack Implementation
q3: | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(SRC_DIR)/dllist.c $(SRC_DIR)/bigint.c $(SRC_DIR)/bigint_ptest.c

# Clean rule
clean:
	rm -f $(BIN_DIR)/*

# Phony targets
.PHONY: all clean q1 q2 q3


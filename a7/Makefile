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
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(SRC_DIR)/tree.c $(SRC_DIR)/queue_stack.c $(SRC_DIR)/tree_ptest.c

# Q2: Stack
q2: | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(SRC_DIR)/bst.c $(SRC_DIR)/bst_ptest.c

# Q3: Expression
q3: | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(SRC_DIR)/bst.c $(SRC_DIR)/myrecord_bst.c  $(SRC_DIR)/myrecord_bst_ptest.c 

# Create zip file for submission
zip:
	cd $(SRC_DIR) && zip ../a6.zip common.h common.c queue.h queue.c stack.h stack.c expression.h expression.c

# Clean rule
clean:
	rm -f $(BIN_DIR)/*

# Phony targets
.PHONY: all clean q1 q2 q3 zip

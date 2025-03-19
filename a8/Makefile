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
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(SRC_DIR)/avl.c $(SRC_DIR)/avl_ptest.c

# Q2: Stack
q2: | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(SRC_DIR)/set_avl.c $(SRC_DIR)/avl.c $(SRC_DIR)/set_avl_ptest.c

# Q3: Expression
q3: | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(SRC_DIR)/myrecord_avl.c $(SRC_DIR)/avl.c $(SRC_DIR)/myrecord_avl_ptest.c

# Create zip file for submission
zip:
	cd $(SRC_DIR) && zip ../a8.zip *

# Clean rule
clean:
	rm -f $(BIN_DIR)/*

# Phony targets
.PHONY: all clean q1 q2 q3 zip

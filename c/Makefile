CC = gcc
CFLAGS =# -g -Wall 

RM = rm -rf

SRC_DIR = ./src
TEST_DIR = ./tests
BUILD_DIR = ./build

SRCS = minheap.c quadratic_probing_hashtable.c array_list.c
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
HDRS = $(SRCS:.o=.h)

TEST_SRCS = test_quadratic_probing_hashtable.c test_minheap.c test_main.c
TEST_OBJS = $(TEST_SRCS:%.c=$(BUILD_DIR)/%.o)

TEST_EXE = datastruct_tests

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@	

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

all: $(OBJS) $(TEST_OBJS)

tests: $(OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(TEST_EXE) $(OBJS) $(TEST_OBJS) 

clean:
	$(RM) $(BUILD_DIR)

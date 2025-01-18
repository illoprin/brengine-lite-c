CC=gcc
CFLAGS=-std=c99 -Wall -g
LDFLAGS=-lglfw -lGLEW -lGLU -lGL -lm

INCLUDE=-I include -I $(SRC_DIR)
SRC_DIR=src
OBJ_DIR=bin

SRCS=$(shell find $(SRC_DIR) -name '*.c')
OBJS=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.obj, $(SRCS))

TARGET=app

# test files
TEST_SRC?=collections.c
TEST_DIR=example
TEST_TARGET=test

all: $(OBJ_DIR)/$(TARGET) | $(OBJ_DIR)
	./$<

clear:
	rm -drf $(OBJ_DIR)

test:
	$(CC) $(CFLAGS) $(LDFLAGS) $(addprefix $(TEST_DIR), /$(TEST_SRC)) -o $(OBJ_DIR)/$(TEST_TARGET) $(INCLUDE)
	./$(OBJ_DIR)/$(TEST_TARGET)

$(OBJ_DIR)/$(TARGET): $(OBJS) | $(OBJ_DIR)
	@echo Linking...
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.obj: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo Compiling $<...
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

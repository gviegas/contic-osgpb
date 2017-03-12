#
# Created by Gustavo Viegas on 2017/02
#

SRC_DIR = src
INC_DIR = include
TEST = test/test.c

OBJS = $(SRC_DIR)/*

CC = gcc
FLAGS = -I$(INC_DIR)
OUT = bin/alpha

all: $(OBJS)
		$(CC) -Wall $(OBJS) $(FLAGS) $(TEST) -o $(OUT)
clean: 
	rm -f bin/*
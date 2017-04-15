#
# Created by Gustavo Viegas on 2017/02
#

SRC_DIR = src
INC_DIR = include
TEST = test/test.c

OBJS = $(SRC_DIR)/* $(TEST)

CC = gcc
OPTS = -Wall
FLAGS = -I$(INC_DIR)
OUT = -o bin/alpha
LIBS = -pthread

all: $(OBJS)
		$(CC) $(OPTS) $(OBJS) $(FLAGS) $(LIBS) $(OUT)

clean: 
		rm -f bin/*
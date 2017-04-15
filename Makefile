#
# Created by Gustavo Viegas on 2017/02
#

SRC_DIR = src
INC_DIR = include

CC = gcc
OPTS = -Wall
FLAGS = -I$(INC_DIR)
LIBS = -pthread
OUT = -o bin/alpha

OBJS = $(SRC_DIR)/*

EXAMPLE_DC = example/example_dc.c
EXAMPLE_UNIT = example/example_unit.c
TEST = test/test.c

all: dc unit test

dc: $(OBJS) $(INC)/*
	$(CC) $(OPTS) $(OBJS) $(EXAMPLE_DC) $(FLAGS) $(LIBS) -o bin/dc

unit: $(OBJS) $(INC)/*
	$(CC) $(OPTS) $(OBJS) $(EXAMPLE_UNIT) $(FLAGS) $(LIBS) -o bin/unit

test: $(OBJS) $(INC)/*
	$(CC) $(OPTS) $(OBJS) $(TEST) $(FLAGS) $(LIBS) -o bin/test

clean:
	rm -f bin/*
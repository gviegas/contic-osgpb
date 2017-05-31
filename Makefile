#
# Created by Gustavo Viegas on 2017/02
#

SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
STAND_DIR = standalone
EXAMPLE_DIR = example
TEST_DIR = test
CMDS_DIR = $(SRC_DIR)/commands
EVENTS_DIR = $(SRC_DIR)/events

CC = gcc
OPTS = -Wall
FLAGS = -I$(INC_DIR)
LIBS = -pthread

OBJS = $(SRC_DIR)/*.c $(CMDS_DIR)/*.c $(EVENTS_DIR)/*.c

UNIT = $(STAND_DIR)/CT_unit_main.c
UNIT_OUT = -o $(BIN_DIR)/unit
DC = $(STAND_DIR)/CT_dc_main.c
DC_OUT = -o $(BIN_DIR)/dc

EXAMPLE_UNIT = $(EXAMPLE_DIR)/example_unit.c
EX_UNIT_OUT = -o $(BIN_DIR)/example_unit
EXAMPLE_DC = $(EXAMPLE_DIR)/example_dc.c
EX_DC_OUT = -o $(BIN_DIR)/example_dc

TEST = $(TEST_DIR)/test.c
TEST_OUT = -o $(BIN_DIR)/test

all: unit dc ex_unit ex_dc test

unit: $(OBJS) $(INC)/*
	$(CC) $(OPTS) $(OBJS) $(UNIT) $(FLAGS) $(LIBS) $(UNIT_OUT)

dc: $(OBJS) $(INC)/*
	$(CC) $(OPTS) $(OBJS) $(DC) $(FLAGS) $(LIBS) $(DC_OUT)

ex_unit: $(OBJS) $(INC)/*
	$(CC) $(OPTS) $(OBJS) $(EXAMPLE_UNIT) $(FLAGS) $(LIBS) $(EX_UNIT_OUT)

ex_dc: $(OBJS) $(INC)/*
	$(CC) $(OPTS) $(OBJS) $(EXAMPLE_DC) $(FLAGS) $(LIBS) $(EX_DC_OUT)

test: $(OBJS) $(INC)/*
	$(CC) $(OPTS) $(OBJS) $(TEST) $(FLAGS) $(LIBS) $(TEST_OUT)

clean:
	rm -f bin/*

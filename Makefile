#
# Created by Gustavo Viegas on 2017/02
#

SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
STAND_DIR = standalone
CMDS_DIR = $(SRC_DIR)/commands
EVENTS_DIR = $(SRC_DIR)/events

CC = gcc
OPTS = -Wall -g
FLAGS = -I$(INC_DIR)
LIBS = -pthread

OBJS = $(SRC_DIR)/*.c $(CMDS_DIR)/*.c $(EVENTS_DIR)/*.c

UNIT = $(STAND_DIR)/CT_unit_main.c
UNIT_OUT = -o $(BIN_DIR)/unit
DC = $(STAND_DIR)/CT_dc_main.c
DC_OUT = -o $(BIN_DIR)/dc

all: unit dc

unit: $(OBJS) $(INC)/*
	$(CC) $(OPTS) $(OBJS) $(UNIT) $(FLAGS) $(LIBS) $(UNIT_OUT)

dc: $(OBJS) $(INC)/*
	$(CC) $(OPTS) $(OBJS) $(DC) $(FLAGS) $(LIBS) $(DC_OUT)

clean:
	rm -f bin/*

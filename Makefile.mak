#
# Created by Gustavo Viegas on 2017/02
#

SRC_DIR = src
INC_DIR = include
TEST = test\test.c

OBJS = $(SRC_DIR)\*.c \
    $(TEST)
#OBJS = $(TEST)

CC = cl
FLAGS = /I$(INC_DIR)
OUT = /Fobin\ /Febin\alpha.exe

all: 
    $(CC) $(OBJS) $(FLAGS) $(OUT)
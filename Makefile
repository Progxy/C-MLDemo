# OBJS specifies which files to compile as part of the project
OBJS = ml.c utils.c neurons.c matrix.c layers.c

# CC specifies which compiler we're using
CC = gcc

# COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -std=c11 -Wall -Wextra -O3

#LIBS specifies the additional libraries
LIBS = -lm

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = ml

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LIBS) -o $(OBJ_NAME)
# OBJS specifies which files to compile as part of the project
OBJS = ml.c

# CC specifies which compiler we're using
CC = gcc

# Headers files
#HEADERS = 

# COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -std=c11 -Wall -Wextra

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = ml

# LIB_FLAGS specifies the additional library to link
#LIB_FLAGS =

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)
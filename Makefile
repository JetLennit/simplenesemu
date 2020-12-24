GXX = g++
SRC = main.cpp source/*
OUT = main
FLAGS = -static
LIBS = -lmingw32 -lSDL2main -lSDL2

all: ${SRC}
	${GXX} ${SRC} -o ${OUT} ${LIBS} -I headers/

run: all
	./${OUT}
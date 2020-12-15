GXX = g++
SRC = main.cpp
OUT = main.exe
FLAGS = -static
LIBS = -lmingw32 -lSDL2main -lSDL2

all: ${SRC}
	${GXX} ${SRC} -o ${OUT} ${LIBS} 

run: all
	./${OUT}
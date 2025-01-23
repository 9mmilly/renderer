CC=gcc
CFLAGS=-Wall -Werror -O3 -march=native $(shell pkg-config --static --cflags glfw3 gl)
LIBS=$(shell pkg-config --static --libs glfw3 gl)
BIN=bin

${BIN}: obj/main.o
	${CC} ${CFLAGS} ${LIBS} $^ -o $@ ${LIBS}

obj/main.o: src/main.c
	${CC} ${CFLAGS} -c  $^ -o $@ ${LIBS}


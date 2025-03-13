CC=gcc
CFLAGS=-Wall -Werror -O3 -march=native $(shell pkg-config --static --cflags glfw3 gl)
LDFLAGS=$(shell pkg-config --static --libs glfw3 gl) 


SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
LIB=lib/glad

LIBS=$(wildcard $(LIB)/*.c)

BIN=bin

$(BIN): $(OBJ) 
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LIBS)

*.o: *.c
	$(CC) -o $@ -c $< $(CFLAGS)
	 
clean:
	$(RM) -r obj/* src/*.o $(BIN)

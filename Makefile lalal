CC=gcc
CFLAGS=-Wall -Werror -O3 -march=native $(shell pkg-config --static --cflags glfw3 gl)
LDFLAGS=$(shell pkg-config --static --libs glfw3 gl) 


SRC=src
OBJ=obj
LIB=lib/glad

SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
LIBS=$(wildcard $(LIB)/*.c)

BIN=bin

$(BIN): $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LIBS)

$(OBJS): $(SRCS) 
	$(CC) $(CFLAGS) -c  $< -o $@ 
	 
clean:
	$(RM) -r $(OBJ)/* $(BIN)

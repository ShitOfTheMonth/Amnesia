CC=gcc
CFLAGS=-Wall
INCLUDES=-Iinclude

BIN_PATH=bin
SRC_PATH=src

all:
	gcc $(CFLAGS) -o $(BIN_PATH)/amnesia $(INCLUDES) $(SRC_PATH)/*.c

clean:
	rm -vrf bin/*

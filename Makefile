GIT_VERSION := $(shell git describe --always --tags)

CC=gcc
CFLAGS=-Wall -DVERSION=\"$(GIT_VERSION)\"
INCLUDES=-Iinclude

BIN_PATH=bin
SRC_PATH=src

all:
	gcc $(CFLAGS) -o $(BIN_PATH)/amnesia $(INCLUDES) $(SRC_PATH)/*.c

clean:
	rm -vrf bin/*

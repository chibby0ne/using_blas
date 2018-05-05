CC=gcc
LDFLAGS=-lcblas
SRC=main.c
BIN=main

all: $(BIN) main_go

$(BIN): $(SRC)
	$(CC) $^ -Wall -Wpedantic ${LDFLAGS} -o $@

main_go: main_go.go
	go build -o $@ $^

.PHONY: clean

clean:
	rm -f $(BIN) main_go


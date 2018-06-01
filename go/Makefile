SRC=main.c
BIN=main_go

all: $(BIN)

main_go: main_go.go
	go build -o $@ $^

.PHONY: clean

clean:
	rm -f $(BIN)


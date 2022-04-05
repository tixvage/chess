CC = gcc
CFLAGS = -std=c11 -O3 -g -Wall -Wextra -Wstrict-aliasing
CFLAGS += -Wno-pointer-arith -Wno-newline-eof -Wno-unused-parameter -Wno-gnu-statement-expression
CFLAGS += -Wno-gnu-compound-literal-initializer -Wno-gnu-zero-variadic-macro-arguments
CFLAGS += -Ivendor/raylib/src
LDFLAGS += vendor/raylib/src/libraylib.a -ldl -lpthread -lm

SRC  = $(wildcard src/**/*.c) $(wildcard src/*.c)
OBJ_DIR = build
SRC_DIR  := src
OBJ = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%,$(SRC:.c=.o))
BIN = bin

.PHONY: all clean

all: dirs libs game

dirs:
	mkdir -p ./$(BIN)
	mkdir -p ./$(OBJ_DIR)

run: all
	$(BIN)/game

game: $(OBJ)
	$(CC) -o $(BIN)/game $^ $(LDFLAGS)

libs:
	cd vendor/raylib/src && make

debug: game
	valgrind $(BIN)/game

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)

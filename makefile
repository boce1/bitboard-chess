CC=gcc
SRC_DIR=src
BIN_DIR=bin
SRC=$(wildcard $(SRC_DIR)/*.c)
EXEC=$(BIN_DIR)/bitboard_chess

CFLAGS_DEBUG=-Wall -Wextra
CFLAGS_RELEASE=-O2

all: release

release: $(EXEC)_release

debug: $(EXEC)_debug

$(EXEC)_release: $(SRC)
	$(CC) $(CFLAGS_RELEASE) -o $@ $^

$(EXEC)_debug: $(SRC)
	$(CC) $(CFLAGS_DEBUG) -o $@ $^

clean:
	rm -f $(BIN_DIR)/*
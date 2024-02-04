CC=gcc
CFLAGS=-Wall -Wextra -O2
SRC_DIR=ralphs_stdlib/src_files
TEST_DIR=ralphs_stdlib/tests
BIN_DIR=bin
EXECUTABLE=$(BIN_DIR)/main
SOURCES=main.c $(SRC_DIR)/array_list.c $(SRC_DIR)/string_tokens.c
TEST_HEADERS=$(TEST_DIR)/arraylist_test.h $(TEST_DIR)/stdlib_tests.h $(TEST_DIR)/string_tokens_test.h

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) $(TEST_HEADERS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(SOURCES) -o $(EXECUTABLE) $(CFLAGS)

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)


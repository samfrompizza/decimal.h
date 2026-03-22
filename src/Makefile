CC = gcc
AR = ar
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -std=c11
LDFLAGS =
FORMATTER = clang-format
LEAK_CHECKER = valgrind
LEAK_CHECKER_FLAGS = --leak-check=full --show-leak-kinds=all --error-exitcode=1

SRC_DIR = .
TEST_DIR = ./tests
BUILD_DIR = ../build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
REPORT_DIR = ../report

LIB_NAME = s21_decimal.a
TEST_BIN = $(BIN_DIR)/test

LIB_SRCS = $(shell find $(SRC_DIR) -type f -name '*.c' -not -path "*/tests/*" | sed 's|^\./||' | sort)
LIB_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(LIB_SRCS))

TEST_SRCS = $(shell find $(TEST_DIR) -type f -name '*.c' | sed 's|^\./||' | sort)
TEST_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(TEST_SRCS))

UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
	CHECK_LIBS = -lcheck -lm -lpthread -lrt -lsubunit
else
	CHECK_LIBS = -lcheck -lm -lpthread
endif

ifeq ($(GCOV),1)
	CFLAGS += -fprofile-arcs -ftest-coverage -O0
	LDFLAGS += -fprofile-arcs -ftest-coverage
endif

.PHONY: all clean test gcov_report style format leak_check

all: $(LIB_NAME)

$(LIB_NAME): $(LIB_OBJS)
	$(AR) rcs $@ $^

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_BIN)
	$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS) $(LIB_NAME)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LIB_NAME) -o $@ $(CHECK_LIBS) $(LDFLAGS)

gcov_report: clean
	$(MAKE) GCOV=1 test
	lcov --capture --directory $(OBJ_DIR) --output-file $(BUILD_DIR)/coverage.info
	lcov --ignore-errors unused --remove $(BUILD_DIR)/coverage.info '/usr/*' '$(TEST_DIR)/*' --output-file $(BUILD_DIR)/coverage.filtered.info
	genhtml $(BUILD_DIR)/coverage.filtered.info --output-directory $(REPORT_DIR)

style:
	$(FORMATTER) -n $(shell find $(SRC_DIR) $(TEST_DIR) -name '*.c' -o -name '*.h')

format:
	$(FORMATTER) -i $(shell find $(SRC_DIR) $(TEST_DIR) -name '*.c' -o -name '*.h')

leak_check: $(TEST_BIN)
	$(LEAK_CHECKER) $(LEAK_CHECKER_FLAGS) $(TEST_BIN) 2>&1 | grep "ERROR SUMMARY" || true

clean:
	$(RM) $(BUILD_DIR) $(REPORT_DIR) $(LIB_NAME) *.gcno *.gcda *.info
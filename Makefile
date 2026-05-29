CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
LDFLAGS = -lm
TEST_SRCS = $(shell find . -name "*_test.c" -o -name "test.c" 2>/dev/null)
ALL_SRCS = $(shell find . -name "*.c" 2>/dev/null)
SRC_FILES = $(filter-out $(TEST_SRCS), $(ALL_SRCS))
TEST_BINS = $(patsubst %.c,%,$(TEST_SRCS))
.PHONY: all clean test run-tests fmt fmt-check
all: run-tests
$(TEST_BINS): %: %.c $(SRC_FILES)
	$(CC) $(CFLAGS) -I. -I$(shell dirname $<)/../include -o $@ $^ $(LDFLAGS)
test: $(TEST_BINS)
run-tests: test
	@for test in $(TEST_BINS); do \
		echo "=== Running $$test ==="; \
		./$$test || exit 1; \
	done
	@echo "=== All tests passed! ==="
fmt:
	@clang-format -style=LLVM -i $$(find . -regex ".*\.[ch]" 2>/dev/null)
fmt-check:
	@clang-format -style=LLVM --dry-run --Werror $$(find . -regex ".*\.[ch]" 2>/dev/null)
clean:
	@find . -type f -executable -delete 2>/dev/null || true
	@rm -f *.o *.a *.out

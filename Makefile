CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wconversion -Wshadow -std=c11 -Iinclude

COMMON = src/alu.c src/cpu.c src/instructions.c

.PHONY: all main tests clean rebuild

all: main

main:
	$(CC) $(CFLAGS) $(COMMON) src/main.c -o cpu

tests:
	$(CC) $(CFLAGS) $(COMMON) tests/tests.c -o test_cpu

clean:
	rm -f cpu test_cpu

rebuild: clean all
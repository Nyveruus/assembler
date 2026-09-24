CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -O0 -fsanitize=address,undefined
NAME = hack_assembler
SRCS = main.c assembler.c parser.c tables.c
INCLUDE = assembler.h parser.h tables.h

.PHONY: all clean

all: hack_assembler

hack_assembler: $(SRCS) $(INCLUDE)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
clean:
	rm -f $(NAME)

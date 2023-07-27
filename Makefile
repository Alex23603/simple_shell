CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89
OBJS = main.o builtin.o builtin1.o environ.o exits.o getinfo.o history.o lists.o lists1.o \
       memory.o string.o string1.o vars.o shell_loop.o getLine.o parser.o realloc.o tokenizer.o

hsh: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o hsh

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o hsh

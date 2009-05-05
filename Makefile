CC = gcc -Wall -pedantic
CFLAGS = -g -std=c99
CFILES = $(wildcard src/*.c)
OFILES = $(subst src,bin, $(subst .c,.o,$(CFILES)))

all: xpl

xpl:	$(CFILES) $(OFILES)
	$(CC) -o bin/$@ $(OFILES)

clean:
	rm -rf $(OFILES) xpl

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

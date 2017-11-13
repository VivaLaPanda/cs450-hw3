# Makefile for pipe test

all: sudoku.x

# $@ is make shorthand for the thing on the left side of the colon
#   (pipes.x in this case)
# $^ stands for everything on the right side of the colon (the .o files)
sudoku.x: main.o parsetools.o boardvalidate.o chan.o
	gcc -g -pthread -o $@ $^

# $< is the first item after the colon (main.c here)
main.o: main.c
	gcc -g -c -o $@ $<

parsetools.o: parsetools.c
	gcc -c -o $@ $<

boardvalidate.o: boardvalidate.c
    gcc -g -c -pthread -o $@ $<

clean:
	rm -f *.x *.o *~


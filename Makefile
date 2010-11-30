all: macvendor.c
	gcc -ansi -pedantic -Wall -O4 -o macvendor macvendor.c

clean:
	rm -f macvendor

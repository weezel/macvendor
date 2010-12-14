debug:
	gcc -g -ansi -pedantic -Wall -O4 -o macvendor macvendor.c
all: macvendor.c
	gcc -ansi -pedantic -Wall -O4 -o macvendor macvendor.c
	mv -f macvendor ${HOME}/bin

clean:
	rm -f macvendor

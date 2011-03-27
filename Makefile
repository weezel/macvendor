CC=clang

all: macvendor.c
	${CC} -ansi -Wall -o macvendor macvendor.c
	mv -f macvendor ${HOME}/bin

debug:
	${CC} -g -ansi -Wall -o macvendor macvendor.c

clean:
	rm -f macvendor

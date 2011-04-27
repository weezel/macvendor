CC=clang

all: macvendor.c
	${CC} -ansi -Wall -o macvendor macvendor.c
	mv -f macvendor ${HOME}/bin

netfetch: netfetch.c
	${CC} -g -ansi -Wall -o netfetch netfetch.c

debug:
	${CC} -g -ansi -Wall -o macvendor macvendor.c

clean:
	rm -f macvendor *.core

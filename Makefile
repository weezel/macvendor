CC=clang

all: macvendor.c
	${CC} -ansi -Wall -o macvendor macvendor.c
	mv -f macvendor ${HOME}/bin

netfetch: netfetch.c
	${CC} -Wall -o netfetch netfetch.c

debug:
	${CC} -g -ansi -Wall -o macvendor macvendor.c
	${CC} -g -Wall -o netfetch netfetch.c

clean:
	rm -f macvendor *.core

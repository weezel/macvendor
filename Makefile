LIBS=-lcurl
CC=gcc

all: macvendor.c
	${CC} ${LIBS} -ansi -Wall -o macvendor macvendor.c netfetch.c
	mv -f macvendor ${HOME}/bin

netfetch: netfetch.c
	${CC} ${LIBS} -Wall -o netfetch netfetch.c

debug:
	${CC} -g -ansi -Wall -o macvendor macvendor.c
	${CC} -g -Wall -o netfetch netfetch.c

clean:
	rm -f macvendor *.core

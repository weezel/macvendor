LIBS=-lcurl
CC=gcc

all: macvendor.c macvendor.h netfetch.h
	${CC} ${LIBS} -ansi -Wall -o macvendor macvendor.c netfetch.c
	mv -f macvendor ${HOME}/bin

netfetch: netfetch.c netfetch.h
	${CC} ${LIBS} -Wall -o netfetch netfetch.c

debug:
	${CC} -g -ansi -Wall -o macvendor macvendor.c
	${CC} -g -Wall -o netfetch netfetch.c

clean:
	rm -f macvendor *.core

CC=gcc
OS=$(shell uname)

all: macvendor.c macvendor.h netfetch.h
.ifeq ($(OS), Linux)
	LDFLAGS = -lcurl
	${CC} ${LIBS} -ansi -Wall -o macvendor macvendor.c netfetch.c
endif

	mv -f macvendor ${HOME}/bin

.ifeq ($(OS), OpenBSD)

debug:
	CC += -g 

clean:
	rm -f macvendor *.core

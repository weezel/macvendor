CC	 = gcc
CFLAGS	+= -g -Wall -Wextra -pedantic -std=c99
CFLAGS	+= -Wstrict-prototypes -Wmissing-prototypes
CFLAGS	+= -Wmissing-declarations -Wsign-compare
CFLAGS	+= -Wshadow -Wpointer-arith -Wcast-qual
INCLUDES = -I /usr/include
LDFLAGS	 = -lcurl
OS	 = $(shell uname)

ifeq ($(OS), Linux)
	LDFLAGS = -lbsd
endif
ifeq ($(OS), OpenBSD)
	INCLUDES += -I /usr/local/include -L /usr/local/lib
endif

.PHONY: all clean

all: macvendor netfetch
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} ${LDFLAGS} netfetch.o macvendor.o -o macvendor
	mv -f macvendor ${HOME}/bin
clean:
	rm -f macvendor *.core
macvendor:
	${CC} ${CFLAGS} macvendor.c -c -o macvendor.o
netfetch:
	${CC} ${CFLAGS} ${INCLUDES} netfetch.c -c -o netfetch.o

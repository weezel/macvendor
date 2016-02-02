CC	 = clang
CFLAGS	+= -std=c99 -Wall -Wextra -pedantic
CFLAGS	+= -fno-omit-frame-pointer
INCLUDES = -I /usr/include
OS	 = $(shell uname)

ifeq ($(OS), Linux)
	LDFLAGS	 = $(shell pkg-config --libs-only-L libcurl)
	CFLAGS	+= -fsanitize=address
endif

ifeq ($(OS), OpenBSD)
	INCLUDES	+= -I /usr/local/include
	LDFLAGS		+= -L /usr/local/lib $(shell pkg-config --libs libcurl)
endif

.PHONY: all clean macvendor netfetch

all: macvendor netfetch
	${CC} ${CFLAGS} ${INCLUDES} netfetch.o macvendor.o -o macvendor \
		${LDFLAGS}
clean:
	rm -f macvendor *.core *.o
macvendor:
	${CC} ${CFLAGS} macvendor.c -c -o macvendor.o
netfetch:
	${CC} ${CFLAGS} ${INCLUDES} netfetch.c -c -o netfetch.o

CC	 = clang
CFLAGS	+= -std=c99 -Wall -Wextra -pedantic
CFLAGS	+= -Wstrict-prototypes -Wmissing-prototypes
CFLAGS	+= -Wmissing-declarations -Wsign-compare
CFLAGS	+= -Wshadow -Wpointer-arith -Wcast-qual
#CFLAGS	+= -fsanitize=address -fno-omit-frame-pointer
INCLUDES = -I /usr/include
LDFLAGS	 = -lcurl
OS	 = $(shell uname)

#ifeq ($(OS), Linux)
#	INCLUDES += $(pkg-config --libs-only-L libcurl)
#endif
ifeq ($(OS), OpenBSD)
	INCLUDES += -I /usr/local/include
	LDFLAGS += -L /usr/local/lib `curl-config --static-libs`
endif

.PHONY: all clean

all: macvendor netfetch
	${CC} ${CFLAGS} ${INCLUDES} netfetch.o macvendor.o -o macvendor ${LDFLAGS}
	#mv -f macvendor ${HOME}/bin
clean:
	rm -f macvendor *.core *.o
macvendor:
	${CC} ${CFLAGS} macvendor.c -c -o macvendor.o
netfetch:
	${CC} ${CFLAGS} ${INCLUDES} netfetch.c -c -o netfetch.o

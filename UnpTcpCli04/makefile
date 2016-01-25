ALL = tcpcli04
CFLAGS = -Wall -g -D_REENTRANT

all: ${ALL}

tcpcli04 : tcpcli04.cc
	g++ ${CFLAGS} tcpcli04.cc ../lib/libUnpSunyj.a -I ../lib -o tcpcli04

clean:
	rm ${ALL}

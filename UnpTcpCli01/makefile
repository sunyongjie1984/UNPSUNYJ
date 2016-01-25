ALL = tcpcli01
CFLAGS = -Wall -g -D_REENTRANT

all: ${ALL}

tcpcli01 : tcpcli01.cc
	g++ ${CFLAGS} tcpcli01.cc ../lib/libUnpSunyj.a -I ../lib -o tcpcli01

clean:
	rm ${ALL}

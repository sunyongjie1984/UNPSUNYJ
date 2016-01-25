ALL = ByteOrder
CFLAGS = -Wall -g -D_REENTRANT

all: ${ALL}

ByteOrder: ByteOrder.cc
	g++ ${CFLAGS} ByteOrder.cc ../lib/libUnpSunyj.a -I ../lib -o ByteOrder

clean:
	rm ${ALL}

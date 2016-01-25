ALL = ByteOrder
CFLAGS = -Wall -g -D_REENTRANT

all: ${ALL}

ByteOrder: ByteOrder.cc
	g++ -o ByteOrder ${CFLAGS} ByteOrder.cc ../lib/libUnpSunyj.a

clean:
	rm ${ALL}

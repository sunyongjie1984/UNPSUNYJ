ALL = daytimetcpsrv1
CFLAGS = -Wall -g -D_REENTRANT

all: ${ALL}

daytimetcpsrv1: daytimetcpsrv1.cc
	g++ ${CFLAGS} daytimetcpsrv1.cc ../lib/libUnpSunyj.a -I ../lib -o daytimetcpsrv1

clean:
	rm ${ALL}

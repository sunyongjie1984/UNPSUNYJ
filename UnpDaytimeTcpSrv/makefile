ALL = UnpDaytimetcpsrv
CFLAGS = -Wall -g -D_REENTRANT

all: ${ALL}

UnpDaytimetcpsrv: UnpDaytimetcpsrv.cc
	g++ ${CFLAGS} UnpDaytimetcpsrv.cc ../lib/libUnpSunyj.a -I ../lib -o UnpDaytimetcpsrv

clean:
	rm ${ALL}

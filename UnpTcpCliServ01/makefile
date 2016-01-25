ALL = tcpserv01
CFLAGS = -Wall -g -D_REENTRANT

all: ${ALL}

#tcpserv01 : tcpserv01.cc sigchldwait.cc
	#g++ ${CFLAGS} tcpserv01.cc sigchldwait.cc ../lib/libUnpSunyj.a -I ../lib -o tcpserv01
tcpserv01 : tcpserv01.cc sigchldwaitpid.cc
	g++ ${CFLAGS} tcpserv01.cc sigchldwaitpid.cc ../lib/libUnpSunyj.a -I ../lib -o tcpserv01

clean:
	rm ${ALL}

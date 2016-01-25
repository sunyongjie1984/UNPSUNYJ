ALL = daytimetcpcli
CFLAGS = -Wall -g -D_REENTRANT

all: ${ALL}

daytimetcpcli: daytimetcpcli.cpp
	g++ ${CFLAGS} daytimetcpcli.cpp ../lib/libUnpSunyj.a -I ../lib -o daytimetcpcli

clean:
	rm ${ALL}

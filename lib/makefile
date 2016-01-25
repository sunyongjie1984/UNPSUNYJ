libUnpSunyj.a : writen.o error.o str_echo.o readline.o str_cli.o wrapstdio.o signal.o
	ar cr libUnpSunyj.a writen.o error.o str_echo.o readline.o str_cli.o wrapstdio.o signal.o
error.o : error.cc unpsunyj.h
	#g++ -c -g -Wall error.cc -o error.o
	g++ -c -g -D_REENTRANT -Wall error.cc -o error.o
writen.o :
	g++ -c -g -D_REENTRANT -Wall writen.cc -o writen.o
str_echo.o :
	g++ -c -g -D_REENTRANT -Wall str_echo.cc -o str_echo.o
readline.o :
	g++ -c -g -D_REENTRANT -Wall readline.cc -o readline.o
str_cli.o :
	g++ -c -g -D_REENTRANT -Wall str_cli.cc -o str_cli.o
wrapstdio.o :
	g++ -c -g -D_REENTRANT -Wall wrapstdio.cc -o wrapstdio.o
signal.o :
	g++ -c -g -D_REENTRANT -Wall signal.cc -o signal.o
clean:
	rm -f *.o libUnpSunyj.a

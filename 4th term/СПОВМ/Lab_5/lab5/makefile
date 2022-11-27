all:
	g++ -ansi -Wall -c -o dynlib.o dynamic_library.cpp
	g++ -shared -o librw.so dynlib.o
	g++ library.h main.cpp -o lab5 -pthread -ldl -rdynamic
	./lab5

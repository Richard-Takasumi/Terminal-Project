output: main.o file_sys.o cli.o utils.o
	g++ main.o file_sys.o cli.o utils.o -o Pa3


main.o: main.cpp file_sys.h utils.h cli.h
	g++ -c main.cpp

file_sys.o: file_sys.cpp file_sys.h utils.h
	g++ -c file_sys.cpp

cli.o: cli.cpp cli.h utils.h file_sys.h
	g++ -c cli.cpp

utils.o: utils.cpp utils.h file_sys.h
	g++ -c utils.cpp

clean:
	rm *.o Pa3
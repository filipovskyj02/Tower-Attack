output: main.o CMenu.o
	g++ -Wall -pedantic -g main.o CMenu.o -lncurses

main.o: main.cpp
	g++ -Wall -pedantic -g -c main.cpp -lncurses

CMenu.o: CMenu.cpp CMenu.hpp
	g++ -Wall -pedantic -g -c CMenu.cpp CMenu.hpp -lncurses

clean: 
	rm *.o *.out

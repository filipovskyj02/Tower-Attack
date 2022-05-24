output: main.o CMenu.o CGame.o
	g++ -Wall -pedantic -g main.o CMenu.o CGame.o -lncurses

main.o: main.cpp
	g++ -Wall -pedantic -g -c main.cpp -lncurses

CMenu.o: CMenu.cpp CMenu.hpp
	g++ -Wall -pedantic -g -c CMenu.cpp CMenu.hpp -lncurses

CGame.o: CGame.cpp CGame.hpp
	g++ -Wall -pedantic -g -c CGame.cpp CGame.hpp -lncurses

clean: 
	rm *.o *.out

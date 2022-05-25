output: main.o CMenu.o CGame.o CMap.o CCell.o
	g++ -Wall -pedantic -g main.o CMenu.o CGame.o CMap.o CCell.o -lncurses

main.o: main.cpp
	g++ -Wall -pedantic -g -c main.cpp -lncurses

CMenu.o: CMenu.cpp CMenu.hpp
	g++ -Wall -pedantic -g -c CMenu.cpp CMenu.hpp -lncurses

CGame.o: CGame.cpp CGame.hpp
	g++ -Wall -pedantic -g -c CGame.cpp CGame.hpp -lncurses

CMap.o: CMap.cpp CMap.hpp
	g++ -Wall -pedantic -g -c CMap.cpp CMap.hpp -lncurses	

CCell.o: CCell.cpp CCell.hpp
	g++ -Wall -pedantic -g -c CCell.cpp CCell.hpp -lncurses	

clean: 
	rm *.o *.out

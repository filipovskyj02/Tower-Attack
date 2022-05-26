output: main.o CMenu.o CGame.o CMap.o CCell.o CAir.o CWall.o CNewLine.o CEnterance.o CExit.o CAttacker.o CHogRider.o
	g++ -Wall -pedantic -g main.o CMenu.o CGame.o CMap.o CCell.o CAir.o CWall.o CNewLine.o CEnterance.o CExit.o CAttacker.o CHogRider.o -lncurses

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

CAir.o: CAir.cpp CAir.hpp
	g++ -Wall -pedantic -g -c CAir.cpp CAir.hpp -lncurses		

CWall.o: CWall.cpp CWall.hpp
	g++ -Wall -pedantic -g -c CWall.cpp CWall.hpp -lncurses	

CNewLine.o: CNewLine.cpp CNewLine.hpp
	g++ -Wall -pedantic -g -c CNewLine.cpp CNewLine.hpp -lncurses	

CEnterance.o: CEnterance.cpp CEnterance.hpp
	g++ -Wall -pedantic -g -c CEnterance.cpp CEnterance.hpp -lncurses

CExit.o: CExit.cpp CExit.hpp
	g++ -Wall -pedantic -g -c CExit.cpp CExit.hpp -lncurses

CAttacker.o: CAttacker.cpp CAttacker.hpp
	g++ -Wall -pedantic -g -c CAttacker.cpp CAttacker.hpp -lncurses

CHogRider.o: CHogRider.cpp CHogRider.hpp
	g++ -Wall -pedantic -g -c CHogRider.cpp CHogRider.hpp -lncurses	
clean: 
	rm *.o *.out *.hpp.gch

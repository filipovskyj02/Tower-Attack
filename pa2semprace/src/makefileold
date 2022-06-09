output: main.o CMenu.o CGame.o CMap.o CCell.o CCellBasic.o CAttacker.o CHogRider.o CMapLoadMap.o CMapPathFind.o CMapRedraw.o CMapPlaceTowers.o CTower.o CLaserTurret.o CMapScout.o CTank.o CGameConfParse.o SConf.o CGameSave.o
	g++ -Wall -pedantic -g main.o CMenu.o CGame.o CMap.o CCell.o CCellBasic.o CAttacker.o CHogRider.o CMapLoadMap.o CMapPathFind.o CMapRedraw.o CMapPlaceTowers.o CTower.o CLaserTurret.o CMapScout.o CTank.o CGameConfParse.o SConf.o CGameSave.o -lncurses

main.o: main.cpp
	g++ -Wall -pedantic -g -c main.cpp -lncurses

CMenu.o: CMenu.cpp CMenu.hpp
	g++ -Wall -pedantic -g -c CMenu.cpp CMenu.hpp -lncurses

CGame.o: CGame.cpp CGameConfParse.cpp CGameSave.cpp CGame.hpp
	g++ -Wall -pedantic -g -c CGame.cpp CGame.hpp -lncurses

CMap.o: CMap.cpp CMapLoadMap.cpp CMapPathFind.cpp CMapRedraw.cpp CMapPlaceTowers.cpp CMap.hpp
	g++ -Wall -pedantic -g -c CMap.cpp CMapLoadMap.cpp CMapPathFind.cpp CMapRedraw.cpp CMapPlaceTowers.cpp CMap.hpp -lncurses

CCell.o: CCell.cpp CCell.hpp
	g++ -Wall -pedantic -g -c CCell.cpp CCell.hpp -lncurses	

CCellBasic.o: CCellBasic.cpp CCellBasic.hpp
	g++ -Wall -pedantic -g -c CCellBasic.cpp CCellBasic.hpp -lncurses		

CAttacker.o: CAttacker.cpp CAttacker.hpp
	g++ -Wall -pedantic -g -c CAttacker.cpp CAttacker.hpp -lncurses

CHogRider.o: CHogRider.cpp CHogRider.hpp
	g++ -Wall -pedantic -g -c CHogRider.cpp CHogRider.hpp -lncurses	

CTower.o: CTower.cpp CTower.hpp
	g++ -Wall -pedantic -g -c CTower.cpp CTower.hpp -lncurses

CLaserTurret.o: CLaserTurret.cpp CLaserTurret.hpp
	g++ -Wall -pedantic -g -c CLaserTurret.cpp CLaserTurret.hpp -lncurses	
CMapScout.o: CMapScout.cpp CMapScout.hpp
	g++ -Wall -pedantic -g -c CMapScout.cpp CMapScout.hpp -lncurses	
CTank.o: CTank.cpp CTank.hpp
	g++ -Wall -pedantic -g -c CTank.cpp CTank.hpp -lncurses	
SConf.o: SConf.cpp SConf.hpp
	g++ -Wall -pedantic -g -c SConf.cpp SConf.hpp -lncurses	
clean: 
	rm *.o *.out *.hpp.gch

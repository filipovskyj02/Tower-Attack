PROG            := filipj25

CXX             := g++

LD_FLAGS        := -Wall --pedantic -g
CXX_FLAGS       := $(LD_FLAGS) -c

OBJS            := main.o CMenu.o CGame.o CMap.o CCell.o CCellBasic.o CAttacker.o CHogRider.o CMapLoadMap.o CMapPathFind.o CMapRedraw.o CMapPlaceTowers.o CTower.o CLaserTurret.o CMapScout.o CTank.o CGameConfParse.o SConf.o CGameSave.o CCannon.o

output: $(OBJS)
	$(CXX) $(LD_FLAGS) -o $(PROG) $(OBJS) -lncurses

%.o: src/%.cpp
	$(CXX) $(CXX_FLAGS) $<
   
doc: doc src/*.hpp
	doxygen Doxyfile

zip: examples/ src/ Doxyfile Makefile prohlaseni.txt zadani.txt
	zip -r $(PROG).zip * 

run: $(PROG)
	./$(PROG)

all:
	make
	make doc

compile:
	make

clean:
	rm *.o $(PROG)
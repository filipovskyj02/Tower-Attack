NAME            := filipj25

VALGRIND_OUT	:= valgrind.txt
CXX             := g++

LD_FLAGS        := -Wall --pedantic -g -std=c++17 -O2
CXX_FLAGS       := $(LD_FLAGS) -c

OBJS            := main.o CMenu.o CGame.o CMap.o CCell.o CTower2.o CCellBasic.o CAttacker.o CHogRider.o CMapLoadMap.o CMapPathFind.o CMapRedraw.o CMapPlaceTowers.o CTower.o CLaserTurret.o CMapScout.o CTank.o CGameConfParse.o SConf.o CGameSave.o 

output: $(OBJS)
	$(CXX) $(LD_FLAGS) -o $(NAME) $(OBJS) -lncurses

%.o: src/%.cpp
	$(CXX) $(CXX_FLAGS) $<
   
doc:
	doc src/*.hpp
	doxygen Doxyfile

opendoc:
	google-chrome doc/index.html

run: 
	compile
	./$(NAME)

count:
	wc -l src/*.cpp
	wc -l src/*.hpp

valgrind: 
	compile
	valgrind ./$(NAME) 2> $(VALGRIND_OUT) 


all:
	make
	make doc

compile:
	make

clean:
	rm *.o  $(NAME)
	
	rm $(VALGRIND_OUT) out.txt movesTaken.txt out.txt
	rm -r doc

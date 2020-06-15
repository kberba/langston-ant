
runAnt: mainAnt.o Ant.o
	g++ -std=c++11 mainAnt.o Ant.o -o runAnt

mainAnt.o: mainAnt.cpp
	g++ -std=c++11 -c mainAnt.cpp

Ant.o: Ant.cpp Ant.hpp
	g++ -std=c++11 -c Ant.cpp

clean:
	rm *.o runAnt

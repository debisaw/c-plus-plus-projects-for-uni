CXX = g++
CXXFLAGS = -Wall

proj2: Hero.o Game.o proj2.cpp
	$(CXX) $(CXXFLAGS) Hero.o Game.o proj2.cpp -o proj2

Game.o: Hero.o Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c Game.cpp

Hero.o: Hero.cpp Hero.h Dance.h
	$(CXX) $(CXXFLAGS) -c Hero.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj2

CXX = g++
CXXFLAGS= -Wall

proj5: Racer.o Racecar.o Truck.o Formula.o Race.h Lqueue.h driver.cpp
	$(CXX) $(CXXFLAGS) Racer.o Racecar.o Truck.o Formula.o  Race.h Lqueue.h driver.cpp -o proj5

Formula.o: Racer.o Formula.cpp Formula.h
	$(CXX) $(CXXFLAGS) -c Formula.cpp

Truck.o: Racer.o Truck.cpp Truck.h
	$(CXX) $(CXXFLAGS) -c Truck.cpp

Racecar.o: Racer.o Racecar.cpp Racecar.h
	$(CXX) $(CXXFLAGS) -c Racecar.cpp
Racer.o: Racer.h Racer.cpp
	$(CXX) $(CXXFLAGS) -c Racer.cpp

run:
	./proj5
val:
	valgrind ./proj5

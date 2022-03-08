CXX = g++
CXXFLAGS= -Wall

proj4: Animal.o Safari.o Gazelle.o Elephant.o Lion.o Herbivore.o Carnivore.o driver.cpp
	$(CXX) $(CXXFLAGS) Animal.o Safari.o Gazelle.o Elephant.o Lion.o Herbivore.o Carnivore.o driver.cpp -o proj4

Safari.o: Animal.o Lion.o Gazelle.o Elephant.o Herbivore.o Carnivore.o Safari.cpp
	$(CXX) $(CXXFLAGS) -c Safari.cpp
Carnivore.o: Animal.o Lion.o Carnivore.cpp Carnivore.h
	$(CXX) $(CXXFLAGS) -c Carnivore.cpp
Herbivore.o: Animal.o Elephant.o Gazelle.o Herbivore.cpp Herbivore.h
	$(CXX) $(CXXFLAGS) -c Herbivore.cpp 
Lion.o: Animal.o Lion.cpp Lion.h
	$(CXX) $(CXXFLAGS) -c Lion.cpp
Elephant.o: Animal.o Elephant.cpp Elephant.h
	$(CXX) $(CXXFLAGS) -c Elephant.cpp
Gazelle.o: Animal.o Gazelle.cpp Gazelle.h
	$(CXX) $(CXXFLAGS) -c Gazelle.cpp
Animal.o: Animal.h Animal.cpp
	$(CXX) $(CXXFLAGS) -c Animal.cpp

run:
	./proj4
run1:
	./proj4 proj4_t1.txt

run2:
	./proj4 proj4_t2.txt

run3:
	./proj4 proj4_t3.txt
val1:
	valgrind ./proj4 proj4_t1.txt
val2:
	valgrind ./proj4 proj4_t2.txt
val3:
	valgrind ./proj4 proj4_t3.txt

clean:
	rm *.o*
	rm *~

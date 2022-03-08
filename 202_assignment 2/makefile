CXX = g++
CXXFLAGS = -Wall

proj3: LL.o Sequencer.o driver.cpp
	$(CXX) $(CXXFLAGS) LL.o Sequencer.o driver.cpp -o proj3

Sequencer.o: LL.o Sequencer.cpp Sequencer.h
	$(CXX) $(CXXFLAGS) -c Sequencer.cpp

LL.o: LL.cpp LL.h
	$(CXX) $(CXXFLAGS) -c LL.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj3

run1:
	./proj3 proj3_test1.txt

run2:
	./proj3 proj3_test2.txt

run3:
	./proj3 proj3_test3.txt

val1:
	valgrind ./proj3 proj3_test1.txt

val2:
	valgrind ./proj3 proj3_test2.txt

val3:
	valgrind ./proj3 proj3_test3.txt

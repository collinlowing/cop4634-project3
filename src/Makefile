CXX = g++
CXXFLAGS = -std=c++11 -Wall -ftest-coverage -fprofile-arcs -pthread -lpthread -lrt

OBJECTS = semaphore.o


lizard: lizard.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) *.o *.gc* *.dSYM test/test core lizard

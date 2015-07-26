CXXFLAGS= -O -Wall -g -std=c++0x -MMD
CXX=g++
CPP_FILES = $(wildcard *.cpp)
OBJECTS = ${CPP_FILES:.cpp=.o}
DEPENDS = ${OBJECTS:.o=.d}
EXEC=hangman

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)


clean:
	rm -f *.o $(EXEC) $(TESTS) $(DEPENDS)

zip :
		zip hangman.zip *.cpp *.h Makefile

-include ${DEPENDS}

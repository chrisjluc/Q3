CXXFLAGS= -O -Wall -g -std=c++0x -MMD
CXX=g++
OBJECTS = MenuComponent.o MenuItem.o Menu.o IteratorTestHarness.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC=menu

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS) 


clean:
	rm -f *.o $(EXEC) $(TESTS) $(DEPENDS)

-include ${DEPENDS}
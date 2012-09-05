SOURCES=play.cpp  nim.cpp  fourinarow.cpp tree.cpp

CXX=g++

CXXFLAGS=-O3 -Wall

INCLUDES=
LDFLAGS=-lpthread

OBJECTS=$(SOURCES:.cpp=.o)
HEADERS=$(SOURCES:.cpp=.h)

%.o : %.cpp 
	$(CXX) -I. $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	
play:$(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

clean:
	rm -f *.o play


play.o:			Makefile 	play.cpp 		nim.o 			fourinarow.o
nim.o:			Makefile 	nim.cpp 		nim.h 			tree.o 
fourinarow.o: 	Makefile 	fourinarow.h 	fourinarow.cpp 	tree.o 
tree.o:			Makefile	tree.h			tree.cpp		graph.h

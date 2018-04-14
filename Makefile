#Makefile

CXX=g++
CXXFLAGS=-std=c++1y -Wall -pedantic
PROG=-o rat
SOURCES=main.cc scanner.cc FSM.cc Parser.cc token.cc
HEADERS=scanner.hh FSM.hh Parser.hh token.hh syntax_error.hh

all: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(PROG) $(SOURCES)

debug: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -g -o rat_debug $(SOURCES)

clean:
	rm -f rat rat_debug






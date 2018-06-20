#Makefile

CXX=g++
CXXFLAGS=-std=c++1y -Wall -pedantic -g
PROG=-o rat
SOURCES=main.cc scanner.cc FSM.cc Parser.cc token.cc SymbolTable.cc
HEADERS=scanner.hh FSM.hh Parser.hh token.hh SymbolTable.hh

all: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(PROG) $(SOURCES)

clean:
	rm -f rat






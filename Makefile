#
	CXX=g++
	CXXFLAGS=-std=c++11 -Wall -pedantic
	PROG=rat

all: main.cc scanner.hh scanner.cc FSM.hh FSM.cc Parser.hh Parser.cc ParseError.hh
	$(CXX) -std=c++1y  -g -Wall -pedantic -o $(PROG) main.cc token.cc scanner.cc Parser.cc FSM.cc

debug:	main.cc scanner.hh scanner.cc FSM.hh FSM.cc Parser.hh Parser.cc ParseError.hh
	$(CXX) -g -o rat_debug main.cc token.cc scanner.cc Parser.cc FSM.cc

clean:
	rm -f rat rat_debug






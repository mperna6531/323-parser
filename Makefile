#

all: main.cc scanner.hh scanner.cc FSM.hh FSM.cc Parser.hh Parser.cc ParseError.hh
	g++ -o rat main.cc token.cc scanner.cc Parser.cc FSM.cc


debug:	main.cc scanner.hh scanner.cc FSM.hh FSM.cc Parser.hh Parser.cc ParseError.hh
	g++ -g -o rat_debug main.cc token.cc scanner.cc Parser.cc FSM.cc

clean:
	rm -f rat rat_debug




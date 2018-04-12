#

all: main.cc scanner.hh scanner.cc FSM.hh FSM.cc Parser.hh Parser.cc ParseError.hh
	g++ -o rat main.cc token.cc scanner.cc Parser.cc FSM.cc

debug:	main.o token.o scanner.o parser.o fsm.o
	g++ -g -o rat_debug rat main.cc token.cc scanner.cc Parser.cc FSM.cc

clean:
	rm -f rat rat_debug



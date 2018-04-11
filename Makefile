#
all: main.cc scanner.hh scanner.cc token.hh token.cc FSM.hh FSM.cc Parser.cc Parser.hh
	g++ -g -o rat main.cc scanner.cc token.cc FSM.cc Parser.cc

clean:
	rm rat 



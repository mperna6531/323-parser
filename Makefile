#
all: main.cc scanner.hh scanner.cc token.hh token.cc FSM.hh FSM.cc Parser.cc Parser.hh
	g++ -g -o rat main.o scanner.o token.o FSM.o Parser.o


clean:
	rm rat 



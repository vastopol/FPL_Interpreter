# Makefile for FP_REPL

# Variables
COMP = g++
FLAGS = -Wall -Werror -ansi -pedantic
DEBUG = -g
OFILES = source/syscom.o source/memory.o source/pattern.o source/interpreter.o source/action.o source/node.o

# Targets
main: main.cpp $(OFILES) | bin
	$(COMP) $(FLAGS) $(OFILES) main.cpp -o fplr && mv fplr bin/
	
debug:
	$(COMP) $(FLAGS) $(DEBUG) $(OFILES) main.cpp -o fplr && mv fplr bin/

syscom.o: source/syscom.cpp header/syscom.h
	$(COMP) $(FLAGS) -c source/syscom.cpp

memory.o: source/memory.cpp header/memory.h
	$(COMP) $(FLAGS) -c source/memory.cpp

pattern.o: source/pattern.cpp header/pattern.h source/interpreter.cpp header/interpreter.h source/action.cpp header/action.h source/node.cpp header/node.h
	$(COMP) $(FLAGS) -c source/pattern.cpp

interpreter.o: source/interpreter.cpp header/interpreter.h source/node.cpp header/node.h
	$(COMP) $(FLAGS) -c source/interpreter.cpp
	
action.o: source/action.cpp header/action.h source/node.cpp header/node.h
	$(COMP) $(FLAGS) -c source/action.cpp

node.o: source/node.cpp header/node.h
	$(COMP) $(FLAGS) -c source/node.cpp
		
bin:
	mkdir bin
	
clean:
	rm -rf bin && rm source/*.o

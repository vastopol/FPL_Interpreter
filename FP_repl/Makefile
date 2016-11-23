# Makefile for FP_REPL

# Variables
COMP = g++
FLAGS = -Wall -Werror -ansi -pedantic
DEBUG = -g
OFILES = source/syscom.o source/interpreter.o source/memory.o

# Targets
main: main.cpp $(OFILES) | bin
	$(COMP) $(FLAGS) $(OFILES) main.cpp -o fplr && mv fplr bin/
	
debug:
	$(COMP) $(FLAGS) $(DEBUG) $(OFILES) main.cpp -o fplr && mv fplr bin/

memory.o: source/memory.cpp header/memory.h
	$(COMP) $(FLAGS) -c source/memory.cpp
	
syscom.o: source/syscom.cpp header/syscom.h
	$(COMP) $(FLAGS) -c source/syscom.cpp
	
interpreter.o: source/interpreter.cpp header/interpreter.h
	$(COMP) $(FLAGS) -c source/interpreter.cpp
		
bin:
	mkdir bin
	
clean:
	rm -rf bin && rm source/*.o

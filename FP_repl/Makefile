# Makefile for FP_REPL

# Variables
COMP = g++
FLAGS = -Wall -Werror -ansi -pedantic
DEBUG = -g
OFILES = source/syscom.o source/interpreter.o source/mem.o

# Targets
main: main.cpp $(OFILES) | bin
	$(COMP) $(FLAGS) $(OFILES) main.cpp -o fplr && mv fplr bin/
	
debug:
	$(COMP) $(FLAGS) $(DEBUG) $(OFILES) main.cpp -o fplr && mv fplr bin/

mem.o: source/mem.cpp header/mem.h
	$(COMP) $(FLAGS) -c source/mem.cpp
	
syscom.o: source/syscom.cpp header/syscom.h
	$(COMP) $(FLAGS) -c source/syscom.cpp
	
interpreter.o: source/interpreter.cpp header/interpreter.h
	$(COMP) $(FLAGS) -c source/interpreter.cpp
		
bin:
	mkdir bin
	
clean:
	rm -rf bin && rm source/*.o
	
# terrible lazy makefile... for now
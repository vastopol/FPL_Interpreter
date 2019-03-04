# Makefile for FP_REPL

# uses some implicit make variables
# CXX is set to use g++ with c++11 standard

# Variables
CXX = g++ -std=c++11
FLAGS = -Wall -Werror -ansi -pedantic
DEBUG = -g
OFILES = source/syscom.o source/memory.o source/pattern.o source/interpreter.o source/action.o source/node.o source/object.o source/func.o source/utils.o

# Targets
main: main.cpp $(OFILES) | bin
	$(CXX) $(FLAGS) $(OFILES) main.cpp -o fplr && mv fplr bin/

debug: main.cpp $(OFILES) | bin
	$(CXX) $(FLAGS) $(DEBUG) $(OFILES) main.cpp -o fplr && mv fplr bin/

syscom.o: source/syscom.cpp header/syscom.h source/utils.cpp header/utils.h
	$(CXX) $(FLAGS) -c source/syscom.cpp

memory.o: source/memory.cpp header/memory.h source/object.cpp header/object.h
	$(CXX) $(FLAGS) -c source/memory.cpp

pattern.o: source/pattern.cpp header/pattern.h source/interpreter.cpp header/interpreter.h source/action.cpp header/action.h source/node.cpp header/node.h
	$(CXX) $(FLAGS) -c source/pattern.cpp

interpreter.o: source/interpreter.cpp header/interpreter.h source/memory.cpp header/memory.h source/object.cpp header/object.h source/node.cpp header/node.h source/utils.cpp header/utils.h
	$(CXX) $(FLAGS) -c source/interpreter.cpp

action.o: source/action.cpp header/action.h source/object.cpp header/object.h  source/node.cpp header/node.h source/func.cpp header/func.h
	$(CXX) $(FLAGS) -c source/action.cpp

node.o: source/node.cpp header/node.h source/object.cpp header/object.h
	$(CXX) $(FLAGS) -c source/node.cpp

object.o: source/object.cpp header/object.h
	$(CXX) $(FLAGS) -c source/object.cpp

func.o: source/func.cpp header/func.h
	$(CXX) $(FLAGS) -c source/func.cpp

utils.o: source/utils.cpp header/utils.h
	$(CXX) $(FLAGS) -c source/utils.cpp

bin:
	mkdir bin

clean:
	rm -rf bin && rm source/*.o && rm *.dot && rm *.jpg  > /dev/null 2>&1

clear:
	rm *.dot && rm *.jpg > /dev/null 2>&1



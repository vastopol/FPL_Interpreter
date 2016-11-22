# Variables
COMP = g++
FLAGS = -Wall -Werror -ansi -pedantic
DEBUG = -g
FILES = functs/syscom.cpp functs/interpreter.cpp

# Targets
front: 
	$(COMP) $(FLAGS) $(FILES) front.cpp
	
test: test.cpp
		$(COMP) $(FLAGS) test.cpp

debug:
	$(COMP) $(FLAGS) $(DEBUG) $(FILES) front.cpp
	
clean:
	rm a.out
	
# terrible lazy makefile... for now
#ifndef __SYSCOM_H__
#define __SYSCOM_H__

// this should be merged into the interpreter class at some point

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>
#include <stack> 
#include <queue>
#include <list>

#include "memory.h"
#include "object.h"

class Object;
class Element;
class Sequence;
class Function;

    void process(std::string s, Memory* m); /* MASTER CONTROL FUNCTION; decides if SYSCOM || FP_EXPRESSION -> interpreter; psudeo preprocessor  */

    void com(std::string s, Memory* m);  // simple builtins handler for: {help(), exit, clear}
    
    void help(); // help prompt
    
    void let(std::string s, Memory* m);  // variable creaton, mapping name to value
    
    void def(std::string s, Memory* m);  // create function macro, mapping name to value
    
    void rem(std::string s, Memory* m);  // remove var if found
    
    void dump(Memory* m);  // clear all memory content
    
    void bufdump(Memory* m); // clear all buffer content
    
    void print(Memory* m); // print element hash, print list hash
    
    void bufprint(Memory* m);
    
    void load(std::string s, Memory* m); // load content of script file to memory buffer
    
    void run(Memory* m); // execute contents of memory buffer in sequential order

    std::string trimSpace(std::string s); // removes any (leading || trailing) whitespace characters (INTERPRETER)
    
    std::string trimSharp(std::string s); // remove comments (INTERPRETER)

#endif // __SYSCOM_H__
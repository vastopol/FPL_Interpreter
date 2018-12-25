#ifndef __SYSCOM_H__
#define __SYSCOM_H__

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <stack>
#include <queue>
#include <list>

#include "memory.h"
#include "object.h"
#include "node.h"
#include "utils.h"

// forward declare
class Object;
class Element;
class Sequence;
class Function;

void process(std::string s, Memory* m);   // psudeo preprocessor

void com(std::string s, Memory* m);       // branch statement to choose syscom || parse.

void help();                              // show help message, display available system commands for outer interpreter

void fcts();                              // show functions message, display available functions for inner intepreter

void history(Memory* m);                  // print command history

void def(std::string s, Memory* m);       // create function macro, mapping name to value

void let(std::string s, Memory* m);       // variable creaton, sets a variable to the return value of a parsed expression; let x = expr

void rem(std::string s, Memory* m);       // remove var if found

void dump_mem(Memory* m);                 // clear all memory content

void dump_buf(Memory* m);                 // clear all buffer content

void print_mem(Memory* m);                // print all memory content

void print_buf(Memory* m);                // print all buffer content

void write_buf(std::string s, Memory* m); // write 1 line append to buffer

void print_ln(std::string s, Memory* m);  // print line || variable to screen

void load(std::string s, Memory* m);      // load content of script file to memory buffer

void run(Memory* m);                      // execute contents of memory buffer in sequential order

void step(Memory* m);                     // execute 1 command from buffer

void gentree(std::string s, Memory* m);   // parse expression and generate a visual of the AST with system call to Graphviz

void eval(std::string s, Memory* m);      // evaluate an expression

#endif // __SYSCOM_H__

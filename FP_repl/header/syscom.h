#ifndef __SYSCOM_H__
#define __SYSCOM_H__

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>
#include <stack> 
#include <queue>
#include <list>

#include "memory.h"

    void com(std::string str, Memory* m); // simple builtins handler
    
    void help();    // help prompt
    
    void let(std::string s, Memory* m); // variable creaton, mapping name to value
    
    void def(std::string s, Memory* m); // create function macro, mapping name to value
    
    void rem(std::string s, Memory* m); // remove var if found
    
    void dump(Memory* m);   // clear all memory content
    
    void print(Memory* m); // print element hash, print list hash
    
    void load(std::string s, Memory* m); // load content of script file to memory buffer
    
    void run(Memory* m); // execute contents of memory buffer in sequential order

#endif // __SYSCOM_H__
#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <iostream>
#include <string>
#include <stack> 
#include <queue>
#include <iterator>

#include "memory.h"

bool parse(std::string s, Memory& m);       // parse engine

bool isBalanced(std::string s); // refers to brackets, braces, parentheses...


#endif // __INTERPRETER_H__


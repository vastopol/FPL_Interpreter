#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>

#include "object.h"
#include "memory.h"

// forward declare
class Object;
class Element;
class Sequence;

// macros
#define printer(x) std::cout<<x<<std::endl // print debugger

// functions
std::string trimSpace(std::string s);     // removes any (leading || trailing) whitespace characters (for INTERPRETER)

std::string trimSharp(std::string s);     // remove comments (for INTERPRETER)

int func_classifier(std::string);         // what type of function

Sequence* seq_par(std::string val, Memory* m); // used inside of action for list parse in higher order functions/operators

#endif // __UTILS_H__

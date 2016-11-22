#ifndef __COM__
#define __COM__

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>
#include <stack> 
#include <queue>
#include <list>


void com(std::string s); // simple builtins

void help();    // help prompt

void exec(std::string str); // parse internal mockup for definiton

void def(std::string s); // definition, hashing name to value

void rem(std::string s); // access hashes and remove var if found

void print(); // print element hash, print list hash

#endif // __COM__
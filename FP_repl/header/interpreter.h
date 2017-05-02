#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <iostream>
#include <string>
#include <list>
#include <stack> 
#include <queue>
#include <iterator>
#include <cstring> // strtok
#include <cstdlib> // atoi

#include "memory.h"
#include "object.h"
#include "node.h"

class Interpreter
{
    private:
        // Helper functions
        bool isBalanced(std::string s);        // refers to brackets, braces, parentheses...
        
        std::string trimSpace(std::string s);  // removes any (leading || trailing) whitespace characters
        
        std::string par_dot(std::string& s);    // rewrite (f.g):x -> f:(g:x)
        
        void par_colon(std::string& s, std::list<std::string>& lst); // parsing on ':'

        std::list<Object*> postfix(std::list<Object*> lst); // convert from infix to postfix

        Node* buildtree(std::list<Object*> lst); // build the AST

    public:
        Interpreter(){};

        ~Interpreter();
        
        Node* parse(std::string s, Memory* m); // parse engine    
};

#endif // __INTERPRETER_H__


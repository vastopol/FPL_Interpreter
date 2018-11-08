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
        bool isBalanced(std::string s);                                    // refers to brackets, braces, parentheses...

        std::string trimSpace(std::string s);                              // removes any (leading || trailing) whitespace characters

        std::string resolve(std::string& s, Memory* m);                    // resolve all definitions on left to chain of composed primitives

        std::string par_dot(std::string& s);                               // rewrite (f.g):x -> f:(g:x)

        void par_colon(std::string& s, std::list<std::string>& lst);       // parsing on ':'

        std::list<Object*> toklist(std::list<std::string> lst, Memory* m); // construct a list of token objects && substitute variables from Memory

        std::list<Object*> postfix(std::list<Object*> lst);                // convert from infix to postfix

        Node* buildtree(std::list<Object*> lst, Memory* m);                // build the AST

    public:
        Interpreter(){};

        ~Interpreter();

        Node* parse(std::string s, Memory* m);                             // parsing engine
};

#endif // __INTERPRETER_H__

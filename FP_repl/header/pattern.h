#ifndef __PATTERN_H__
#define __PATTERN_H__

#include <string>
#include <iostream>

#include "action.h"
#include "interpreter.h"
#include "node.h"

class Pattern
{
    private:
        std::string expression;
        Node* root;
        Interpreter* interpreter;
        Action* action;
        
    public:
        Pattern(std::string);
        ~Pattern();
        
        void setRoot(Node*); // set a root
        Node* getRoot();     // get root of abstract syntax tree
        Interpreter* getI(); // get interpreter object
        Action* getA();      // get execution object
    
};

#endif // __PATTERN_H__
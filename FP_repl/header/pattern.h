#ifndef __PATTERN_H__
#define __PATTERN_H__

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

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
        Pattern(std::string s);
        ~Pattern();
        
        void setRoot(Node* n); // set a root
        Node* getRoot();     // get root of abstract syntax tree
        Interpreter* getI(); // get interpreter object
        Action* getA();      // get execution object

        //Printing
        void preOrder(Node* n);
        void inOrder(Node* n);
        void postOrder(Node* n);
        
        // genterate tree with system call to graphviz (based on code from cs14)
        void generateTree(std::ofstream& out, Node* n);
        void visualizeTree(const std::string& outputFilename);  
};

#endif // __PATTERN_H__
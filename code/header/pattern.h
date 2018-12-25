#ifndef __PATTERN_H__
#define __PATTERN_H__

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stack>

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

        // hidden part for type checking
        std::stack<std::string> secret_stk;
        void postOrderCheck(Node* n);

    public:
        Pattern(std::string s);
        ~Pattern();

        void setRoot(Node* n);      // set a root
        Node* getRoot();            // get root of abstract syntax tree
        Interpreter* getI();        // get interpreter object
        Action* getA();             // get execution object

        // Printing
        void preOrder(Node* n);
        void inOrder(Node* n);
        void postOrder(Node* n);

        // type check traverse
        std::stack<std::string> postOrderCheckWrap(Node* n);

        // genterate tree with system call to graphviz
        void generateTree(std::ofstream& out, Node* n, int i); // recursive

        // visualizeTree is a wrapper that then calls generateTree
        void visualizeTree(const std::string& outputFilename);
};

#endif // __PATTERN_H__

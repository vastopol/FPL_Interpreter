#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <iostream>

class Node
{
    private:
        std::string key;
        Node* parent;
        Node* left;
        Node* right;
        
    public:
        Node(std::string);
        ~Node();
        
        std::string getkey();
        Node* getParent();
        Node* getLeft();
        Node* getRight();
        void setParent(Node*);
        void setLeft(Node*);
        void setRight(Node*);
};

#endif // __NODE_H__
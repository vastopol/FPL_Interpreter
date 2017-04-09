#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <iostream>

#include "object.h"

class Node
{
    private:
        Object* key;
        Node* parent;
        Node* left;
        Node* right;
        
    public:
        Node(Object*);
        ~Node();
        
        Object* getkey();
        Node* getParent();
        Node* getLeft();
        Node* getRight();
        void setParent(Node*);
        void setLeft(Node*);
        void setRight(Node*);
};

#endif // __NODE_H__
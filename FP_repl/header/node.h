#ifndef __NODE_H__
#define __NODE_H__

#include <string>

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
};

#endif // __NODE_H__
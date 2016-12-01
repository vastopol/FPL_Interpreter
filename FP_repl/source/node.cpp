#include "../header/node.h"

Node::Node(std::string s)
    : key(s), parent(0), left(0), right(0)
{}
//--------------------------------------------------

Node::~Node()
{
}
//--------------------------------------------------
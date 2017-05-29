#ifndef __ACTION_H__
#define __ACTION_H__

#include <iostream>

#include "node.h"
#include "object.h"
#include "func.h"

class Action
{
    public:
        Action();
        ~Action();
        
        Object* exec(Node* n); // tree traversal

        Object* apply(Object* fun, Object* arg); //  fun(arg)
};

#endif // __ACTION_H__
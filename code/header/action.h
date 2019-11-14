#ifndef __ACTION_H__
#define __ACTION_H__

#include <iostream>

#include "node.h"
#include "object.h"
#include "func.h" // Action class cant work with out the functions in func.h/cpp
#include "operator.h"
#include "utils.h"
#include "memory.h"

class Action
{
    public:
        Action();
       ~Action();

        Object* exec(Node* n, Memory* m); // tree traversal

        Object* apply(Object* fun, Object* arg, Memory* m); //  fun(arg)
};

#endif // __ACTION_H__

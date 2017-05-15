#ifndef __ACTION_H__
#define __ACTION_H__

#include <iostream>
#include "node.h"

class Action
{
    public:
        Action();
        ~Action();
        
        void exec(Node*); // tree traverse

        void doing(); // function execution
};

#endif // __ACTION_H__
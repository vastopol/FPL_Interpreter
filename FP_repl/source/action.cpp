#include "../header/action.h"

Action::Action()
{}
//--------------------------------------------------------------

Action::~Action()
{
    //   std::cout << "ACTION DESTRUCTOR" << std::endl;  
}
//--------------------------------------------------------------

void Action::exec(Node* n)
{
    std::cout << "EXEC" << std::endl;
    
    std::cout << "not done" << std::endl;

    if(n == 0)
    {
        return;
    }
    
    // tree traversal here
}
//--------------------------------------------------------------

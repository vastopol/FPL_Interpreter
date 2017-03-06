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
    std::cout << "EXEC\n" << "not done\n" << std::endl;

    return;
    
    // tree traversal here
}
//--------------------------------------------------------------

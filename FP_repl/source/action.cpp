#include "../header/action.h"

Action::Action()
{}
//--------------------------------------------------------------

Action::~Action()
{
    //   std::cout << "ACTION DESTRUCTOR" << std::endl;  
}
//--------------------------------------------------------------

void Action::exec(Node* n) // tree traverse
{
    std::cout << "\nEXEC\n" << "not done\n" << std::endl;

    if(n == 0) // null tree
    {
    	std::cout << "NULL" << std::endl;
    	return;
    }

    if(n != 0 && n->getKey()->type() != "Colon")
    {
    	std::cout << "KEY:" << std::endl;
    	n->getKey()->print();
    }
    else
    {
    	exec(n->getLeft());

    	n->getKey()->print();

    	exec(n->getRight());
    }

    return;
}    
//--------------------------------------------------------------

void Action::doing() // function execute
{
	return;
}
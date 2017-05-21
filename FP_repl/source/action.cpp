#include "../header/action.h"

Action::Action()
{}
//--------------------------------------------------------------

Action::~Action()
{
    //   std::cout << "ACTION DESTRUCTOR" << std::endl;  
}
//--------------------------------------------------------------

Object* Action::exec(Node* n) // tree traverse
{
    std::cout << "\nEXEC\n" << std::endl;

    if(n == 0) // null tree
    {
    	std::cout << "NULL" << std::endl;
    	return 0;
    }

    if(n != 0 && n->getKey()->type() != "Colon") // fetch
    {
        return n->getKey();
    }
    else // apply
    {
        Object* arg = 0;
        Object* fun = 0;
        Object* res = 0;

    	arg = exec(n->getRight());
        if(arg != 0) { arg->print(); std::cout << std::endl; }
        // if(arg == 0) { std::cout << "ERROR: NULL ARG" << std::endl; return 0;}
    	
        // n->getKey()->print(); // print ':'

    	fun = exec(n->getLeft());
        if(fun != 0) { fun->print(); std::cout << std::endl; }
        // if(fun == 0) { std::cout << "ERROR: NULL FUNCT" << std::endl; return 0;}

        // evaluate expression here
        // res = doing(fun, arg);

        return res;
    }

    return 0;
}    
//--------------------------------------------------------------

Object* Action::doing(Object* fun, Object* arg) // function execute
{
    if(fun == 0 || arg == 0) // error checking null pointers
    { return 0; }

    std::string tag = fun->stringify();

    if(arg->type() == "Element")
    {
    }
    else // sequence
    {
    }

	return 0;
}
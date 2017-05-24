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
        else { std::cout << "ERROR: NULL ARG" << std::endl; return 0;}
    	
        n->getKey()->print(); // print ':'

    	fun = exec(n->getLeft());
        if(fun != 0) { fun->print(); std::cout << std::endl; }
        else { std::cout << "ERROR: NULL FUNCT" << std::endl; return 0;}

        // evaluate expression here
        res = doing(fun, arg);

        return res;
    }

    return 0;
}    
//--------------------------------------------------------------

Object* Action::doing(Object* fun, Object* arg) // function execute
{
    std::cout << "doing" << std::endl;

    if(fun == 0 || arg == 0) // error checking null pointers
    { return 0; }

    std::string tag = fun->stringify();
    Object* ret = 0;
    int op = 0;    


    // have to search for string in opcode map*********

    // type conversion of Object*
    if(arg->type() == "Element")
    {  
        op = U_E[tag];
        if(op == -1){return 0;} 
        Element* el = static_cast<Element*>(arg);
        int x = (*Unary_E[op])(el->getElement());
        ret = new Element(x);
        return ret;
    }
    else // sequence
    {
        op = U_S[tag];
        if(op == -1){return 0;} 
        Sequence* seq = static_cast<Sequence*>(arg);
        std::list<int> l = (*Unary_S[op])(seq->getList());
        ret = new Sequence(l);
        return ret;
    }

	return 0;
}
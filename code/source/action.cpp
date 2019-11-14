#include "../header/action.h"
#include <vector>

Action::Action()
{}
//--------------------------------------------------------------

Action::~Action()
{}
//--------------------------------------------------------------

Object* Action::exec(Node* n, Memory* m) // tree traversal
{
    // std::cout << "\nEXEC\n" << std::endl;

    if(n == 0) // null tree
    {
    	std::cout << "ERROR: NULL" << std::endl;
        throw std::runtime_error("exec() : NULL tree"); // return 0;
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

    	arg = exec(n->getRight(),m);

        if(arg == 0) // if(arg != 0){ arg->print(); std::cout << std::endl; }
        {
            std::cout << "ERROR: NULL ARG" << std::endl;
            throw std::runtime_error("exec() : NULL arg"); // return 0;
        }

        // n->getKey()->print(); // print ':'

    	fun = exec(n->getLeft(),m);

        if(fun == 0) // if(fun != 0){ fun->print(); std::cout << std::endl; }
        {
            std::cout << "ERROR: NULL FUNCT" << std::endl;
            throw std::runtime_error("exec() : NULL function"); // return 0;
        }

        // evaluate expression here
        res = apply(fun, arg, m);
        return res;
    }
    throw std::runtime_error("exec() : ERROR : ERROR"); // return 0;
}
//--------------------------------------------------------------

Object* Action::apply(Object* fun, Object* arg, Memory* m) // function execute
{
    // std::cout << "doing" << std::endl;

    if(fun == 0 || arg == 0) // error checking null pointers
    {
        std::cout << "INPUT ERROR: (FUNCT || ELM) == NULL" << std::endl;
        throw std::runtime_error("apply() : (FUNCT || ELM) == NULL"); // return 0;
    }

    std::string tag = fun->stringify();
    Object* ret = 0;
    int op = 0;     // have to search for opcode corresponding to tag in hashmap

    //----------------------------------------

    // higher order functions/operators
    ret = operate(fun,arg,m);
    if(ret != NULL)
    {
        return ret;
    }

    //----------------------------------------

    // regular functions
    if(arg->type() == "Element")
    {
        if(U_E_R_S.find(tag) != U_E_R_S.end()) // function returning a sequence
        {
          op = U_E_R_S[tag];
          Element* el = static_cast<Element*>(arg);
          std::list<int> l = (*Unary_E_R_S[op])(el->getElement());
          ret = new Sequence(l);
          return ret;
        }

        if(U_E_R_E.find(tag) == U_E_R_E.end())
        {
            std::cout << "ERROR: INVALID FUNCT ELM: " << tag << std::endl;
            throw std::runtime_error("apply() : INVALID FUNCT ELM"); // return 0;
        }

        op = U_E_R_E[tag];
        Element* el = static_cast<Element*>(arg);
        int x = (*Unary_E_R_E[op])(el->getElement());
        ret = new Element(x);
        return ret;
    }
    else // sequence
    {
        if(U_S_R_E.find(tag) != U_S_R_E.end()) // function returning an element
        {
            op = U_S_R_E[tag];
            Sequence* seq = static_cast<Sequence*>(arg);
            int x = (*Unary_S_R_E[op])(seq->getList());
            ret = new Element(x);
            return ret;
        }

        if(U_S_R_S.find(tag) == U_S_R_S.end()) // can cause a segfault if inc is used... unknown bug
        {
            std::cout << "ERROR: INVALID FUNCT SEQ: " << tag << std::endl;
            throw std::runtime_error("apply() : INVALID FUNCT SEQ"); // return 0;
        }

        op = U_S_R_S[tag];
        Sequence* seq = static_cast<Sequence*>(arg);
        std::list<int> l = (*Unary_S_R_S[op])(seq->getList());
        ret = new Sequence(l);
        return ret;
    }

    throw std::runtime_error("apply() : ERROR : ERROR"); // return 0;
}

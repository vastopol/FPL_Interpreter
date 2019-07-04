#include "../header/action.h"


Action::Action()
{}
//--------------------------------------------------------------

Action::~Action()
{
    //   std::cout << "ACTION DESTRUCTOR" << std::endl;
}
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

    // opereators / higher order functions
    if(tag.substr(0,4) == "map{")
    {
        // printer("MAP");
        std::string mop = trimSpace( tag.substr( 4 , tag.size()-4 ) ) ;
        mop.pop_back();
        Object* fu = m->goGet(mop); // function
        if(fu == 0)
        {
            tag = mop;
        }
        else
        {
            tag = fu->stringify();
        }

        if(!mop.empty() && arg->type() == "Sequence" && arg->stringify() != "<>")
        {
            // printer("op: "+op);
            // printer("fu: "+fu->stringify());
            // printer("l1: "+arg->stringify());
            std::list<int> l1 = ((Sequence*)arg)->getList();
            std::list<int> l2;
            for(auto i : l1)
            {
                op = U_E_R_E[tag];
                Element* el = new Element(i);
                int x = (*Unary_E_R_E[op])(el->getElement());
                l2.push_back(x);
                // printer(x);
            }
            return new Sequence(l2);
        }
        else
        {
            printer("ERROR: empty argument to map operator");
            throw std::runtime_error("apply() : map{} operator");
        }
    }

    if(tag.substr(0,5) == "filt{")
    {
        // printer("FILTER");
        std::string mop = trimSpace( tag.substr( 5 , tag.size()-5 ) ) ;
        mop.pop_back();
        Object* fu = m->goGet(mop); // function
        if(fu == 0)
        {
            tag = mop;
        }
        else
        {
            tag = fu->stringify();
        }

        if(!mop.empty() && arg->type() == "Sequence" && arg->stringify() != "<>")
        {
            // printer("op: "+op);
            // printer("fu: "+fu->stringify());
            // printer("l1: "+arg->stringify());
            std::list<int> l1 = ((Sequence*)arg)->getList();
            std::list<int> l2;
            for(auto i : l1)
            {
                op = U_E_R_E[tag];
                Element* el = new Element(i);
                int x = (*Unary_E_R_E[op])(el->getElement());
                if(x == 1)
                {
                    l2.push_back(i);
                }
                // printer(x);
            }
            return new Sequence(l2);
        }
        else
        {
            printer("ERROR: empty argument to filter operator");
            throw std::runtime_error("apply() : filt{} operator");
        }
    }

    if(tag.substr(0,3) == "at{")
    {
        // printer("AT");
        std::string mop = trimSpace( tag.substr( 3 , tag.size()-3 ) ) ;
        mop.pop_back();

        if(!mop.empty() && arg->type() == "Sequence" && arg->stringify() != "<>")
        {
            std::list<int> l1 = ((Sequence*)arg)->getList();
            int ee = 0;
            Object* fu = m->goGet(mop);
            if(fu == 0)
            {
                ee = atoi(mop.c_str());
            }
            else
            {
                ee = atoi( fu->stringify().c_str() );
            }
            // int ee = atoi(mop.c_str());
            // printer(ee);
            // printer(l1.size());
            if(ee > l1.size() || ee < 1)
            {
                printer("ERROR: index to at operator");
                throw std::runtime_error("apply() : at{} operator");
            }
            for(int i = 1; i < ee; i++)
            {
                // printer(l1.front());
                l1.pop_front();
            }
            return new Element(l1.front());
        }
        else
        {
            printer("ERROR: empty argument to at operator");
            throw std::runtime_error("apply() : at{} operator");
        }
    }

    if(tag.substr(0,4) == "apr{")
    {
        // printer("APR");
        std::string mop = trimSpace( tag.substr( 4 , tag.size()-4 ) ) ;
        mop.pop_back();

        if(!mop.empty() && arg->type() == "Sequence")
        {
            std::list<int> l1 = ((Sequence*)arg)->getList();
            int ee = 0;
            Object* fu = m->goGet(mop);
            if(fu == 0)
            {
                ee = atoi(mop.c_str());
            }
            else
            {
                ee = atoi( fu->stringify().c_str() );
            }
            // int ee = atoi(mop.c_str());
            // printer(ee);
            l1.push_back(ee);
            return new Sequence(l1);
        }
        else
        {
            printer("ERROR: empty argument to append right operator");
            throw std::runtime_error("apply() : apr{} operator");
        }
    }

    if(tag.substr(0,4) == "apl{")
    {
        // printer("APL");
        std::string mop = trimSpace( tag.substr( 4 , tag.size()-4 ) ) ;
        mop.pop_back();

        if(!mop.empty() && arg->type() == "Sequence")
        {
            std::list<int> l1 = ((Sequence*)arg)->getList();
            int ee = 0;
            Object* fu = m->goGet(mop);
            if(fu == 0)
            {
                ee = atoi(mop.c_str());
            }
            else
            {
                ee = atoi( fu->stringify().c_str() );
            }
            // int ee = atoi(mop.c_str());
            // printer(ee);
            l1.push_front(ee);
            return new Sequence(l1);
        }
        else
        {
            printer("ERROR: empty argument to append left operator");
            throw std::runtime_error("apply() : apl{} operator");
        }
    }

    //----------------------------------------

    // regular functions
    // type conversion of Object*
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

#include "../header/operator.h"

Object* operate(Object* fun, Object* arg, Memory* m)
{
    std::string tag = fun->stringify();
    Object* ret = 0;
    int op = 0;     // have to search for opcode corresponding to tag in hashmap

    // opereators / higher order functions (special cases)
    if(tag == "id")
    {
        return arg;
    }

    if(tag == "elm")
    {
        if(arg->type() == "Element")
        {
            return new Element(1);
        }
        else
        {
            return new Element(0);
        }
    }

    if(tag == "seq")
    {
        if(arg->type() == "Sequence")
        {
            return new Element(1);
        }
        else
        {
            return new Element(0);
        }
    }

    if(tag.substr(0,4) == "map{")
    {
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
            std::list<int> l1 = ((Sequence*)arg)->getList();
            std::list<int> l2;
            for(auto i : l1)
            {
                op = U_E_R_E[tag];
                Element* el = new Element(i);
                int x = (*Unary_E_R_E[op])(el->getElement());
                l2.push_back(x);
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

            if(ee > l1.size() || ee < 1)
            {
                printer("ERROR: index to at operator");
                throw std::runtime_error("apply() : at{} operator");
            }
            for(int i = 1; i < ee; i++)
            {
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

    if(tag.substr(0,4) == "apr{") // append right
    {
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

            l1.push_back(ee);
            return new Sequence(l1);
        }
        else
        {
            printer("ERROR: empty argument to append right operator");
            throw std::runtime_error("apply() : apr{} operator");
        }
    }

    if(tag.substr(0,4) == "apl{") // append left
    {
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

            l1.push_front(ee);
            return new Sequence(l1);
        }
        else
        {
            printer("ERROR: empty argument to append left operator");
            throw std::runtime_error("apply() : apl{} operator");
        }
    }

    if(tag.substr(0,4) == "cat{")
    {
        std::string mop = trimSpace( tag.substr( 4 , tag.size()-4 ) ) ;
        mop.pop_back();

        if(!mop.empty() && arg->type() == "Sequence")
        {
            std::list<int> l1 = ((Sequence*)arg)->getList();
            std::list<int> l2;

            if(mop.at(0) != '<') // lookup, since errors if the "<" encountered...
            {
                Object* fu = m->goGet(mop);
                if(fu == 0)
                {
                    printer("ERROR: empty argument to concatenate operator");
                    throw std::runtime_error("apply() : cat{} operator");
                }
                else
                {
                    l2 = ((Sequence*)fu)->getList();
                }
            }
            else // parse
            {
                printer(mop);
                Sequence* ssqq = seq_par(mop,m);
                l2 = ssqq->getList();
            }

            for(int i : l2)
            {
                l1.push_back(i);
            }
            return new Sequence(l1);
        }
        else
        {
            printer("ERROR: empty argument to concatenate operator");
            throw std::runtime_error("apply() : cat{} operator");
        }
    }

    if(tag.substr(0,3) == "if{")
    {
        // printer("IF");
        std::string mop = trimSpace( tag.substr( 3 , tag.size()-3 ) ) ;
        mop.pop_back();

        if(!mop.empty())
        {
            //split parameters
            unsigned pos = mop.find(';');
            std::string tmpstr = "";
            std::list<std::string> pargs;
            while( pos != std::string::npos && pos < mop.size() )
            {
                tmpstr = mop.substr(0, pos);
                pargs.push_back(tmpstr);
                mop = mop.substr(pos+1,mop.size()-1);
                pos = mop.find(';');
            }
            if(!mop.empty())
            {
                pargs.push_back(mop);
            }
            if(pargs.size() != 3) // if{p;f1;f2}:x
            {
                printer(pargs.size());
                printer("ERROR: arity of argument to if operator");
                throw std::runtime_error("apply() : if{} operator");
            }

            // get parameters
            std::vector<std::string> vblob;
            for ( std::string stds : pargs )
            {
                Object* fu = m->goGet(stds);
                if(fu == 0)
                {
                    vblob.push_back(stds);
                }
                else
                {
                    vblob.push_back(fu->stringify());
                }
            }

            std::string pred = vblob.at(0);
            std::string tarm = vblob.at(1);
            std::string farm = vblob.at(2);
            int pres;
            int pret;
            std::list<int> lret;

            if(arg->type() == "Sequence")
            {
                std::list<int> l1 = ((Sequence*)arg)->getList();

                if(U_S_R_E.find(pred) != U_S_R_E.end())// predicate must return int (U_S_R_E)
                {
                    op = U_S_R_E[pred];
                    pres = (*Unary_S_R_E[op])(l1);

                    // should check here for function types ?
                    if(pres!=0)
                    {
                        if(U_S_R_E.find(tarm) != U_S_R_E.end())
                        {
                            op = U_S_R_E[tarm];
                            pret = (*Unary_S_R_E[op])(l1);
                            ret = new Element(pret);
                        }
                        else if(U_S_R_S.find(tarm) != U_S_R_S.end())
                        {
                            op = U_S_R_S[tarm];
                            lret = (*Unary_S_R_S[op])(l1);
                            ret = new Sequence(lret);
                        }
                    }
                    else
                    {
                        if(U_S_R_E.find(farm) != U_S_R_E.end())
                        {
                            op = U_S_R_E[farm];
                            pret = (*Unary_S_R_E[op])(l1);
                            ret = new Element(pret);
                        }
                        else if(U_E_R_S.find(farm) != U_E_R_S.end())
                        {
                            op = U_S_R_S[farm];
                            lret = (*Unary_S_R_S[op])(l1);
                            ret = new Sequence(lret);
                        }
                    }
                    return ret;
                }
                else
                {
                    std::cout << "ERROR: INVALID FUNCT SEQ: inside if " << pred << std::endl;
                    throw std::runtime_error("apply() : INVALID FUNCT SEQ"); // return 0;
                }
            }
            else // Element
            {
                int e1 = ((Element*)arg)->getElement();

                if(U_E_R_E.find(pred) != U_E_R_E.end()) // predicate must return int (U_E_R_E)
                {
                    op = U_E_R_E[pred];
                    pres = (*Unary_E_R_E[op])(e1);

                    // should check here for function types ?
                    if(pres!=0)
                    {
                        if(U_E_R_E.find(tarm) != U_E_R_E.end())
                        {
                            op = U_E_R_E[tarm];
                            pret = (*Unary_E_R_E[op])(e1);
                            ret = new Element(pret);
                        }
                        else if(U_E_R_S.find(tarm) != U_E_R_S.end())
                        {
                            op = U_E_R_S[tarm];
                            lret = (*Unary_E_R_S[op])(e1);
                            ret = new Sequence(lret);
                        }
                    }
                    else
                    {
                        if(U_E_R_E.find(farm) != U_E_R_E.end())
                        {
                            op = U_E_R_E[farm];
                            pret = (*Unary_E_R_E[op])(e1);
                            ret = new Element(pret);
                        }
                        else if(U_E_R_S.find(farm) != U_E_R_S.end())
                        {
                            op = U_E_R_S[farm];
                            lret = (*Unary_E_R_S[op])(e1);
                            ret = new Sequence(lret);
                        }
                    }
                    return ret;
                }
                else
                {
                    std::cout << "ERROR: INVALID FUNCT ELM: inside if " << pred << std::endl;
                    throw std::runtime_error("apply() : INVALID FUNCT ELM"); // return 0;
                }
            }
        }
        else
        {
            printer("ERROR: empty argument to if operator");
            throw std::runtime_error("apply() : if{} operator");
        }
    }

    if(tag.substr(0,4) == "ccf{")
    {
        // printer("IF");
        std::string mop = trimSpace( tag.substr( 4 , tag.size()-4 ) ) ;
        mop.pop_back();

        if(!mop.empty())
        {
            //split parameters
            unsigned pos = mop.find(';');
            std::string tmpstr = "";
            std::list<std::string> pargs;
            while( pos != std::string::npos && pos < mop.size() )
            {
                tmpstr = mop.substr(0, pos);
                pargs.push_back(tmpstr);
                mop = mop.substr(pos+1,mop.size()-1);
                pos = mop.find(';');
            }
            if(!mop.empty())
            {
                pargs.push_back(mop);
            }

            // get parameters
            std::vector<std::string> vblob;
            for ( std::string stds : pargs )
            {
                Object* fu = m->goGet(stds);
                if(fu == 0)
                {
                    vblob.push_back(stds);
                }
                else
                {
                    vblob.push_back(fu->stringify());
                }
            }

            // get the arg here
            int iret = 0;
            std::list<int> lret;
            for(std::string i : vblob) // apply and construct loop
            {
                // branch based on the type of the argument
                // apply function to arg.
                // append the result of the function to the return list.
                if(arg->type() == "Sequence")
                {
                    if(U_S_R_E.find(i) != U_S_R_E.end())
                    {
                        op = U_S_R_E[i];
                        iret = (*Unary_S_R_E[op])(((Sequence*)arg)->getList());
                        // ret = new Element(iret);
                    }
                    else
                    {
                        printer("ERROR: type mismatch");
                        throw std::runtime_error("apply() : ccf{} operator");
                    }
                }
                else  // Element
                {
                    if(U_E_R_E.find(i) != U_E_R_E.end())
                    {
                        op = U_E_R_E[i];
                        iret = (*Unary_E_R_E[op])(((Element*)arg)->getElement());
                        // ret = new Element(iret);
                    }
                    else
                    {
                        printer("ERROR: type mismatch");
                        throw std::runtime_error("apply() : ccf{} operator");
                    }
                }
                lret.push_back(iret);
            }
            ret = new Sequence(lret);
            return ret;
        }
        else
        {
            printer("ERROR: empty argument to ccf operator");
            throw std::runtime_error("apply() : ccf{} operator");
        }
    }

    // reduce **********
    if(tag.substr(0,4) == "red{")
    {
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
            op = U_S_R_S[tag];
            std::list<int> l1 = ((Sequence*)arg)->getList();
            std::list<int> l2;
            while(l1.size() > 1)
            {
                l2 = (*Unary_S_R_S[op])(l1);
                l1 = l2;
            }

            int x = l2.front();
            return new Element(x);
        }
        else
        {
            printer("ERROR: empty argument to reduce operator");
            throw std::runtime_error("apply() : red{} operator");
        }
    }

    // END
    return NULL;
}
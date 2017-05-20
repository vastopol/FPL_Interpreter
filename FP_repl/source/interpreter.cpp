#include "../header/interpreter.h"


Interpreter::~Interpreter()
{
    //  std::cout << "INTERPRETER DESTRUCTOR" << std::endl;
}
//------------------------------------------------

Node* Interpreter::parse(std::string str, Memory* m) // parse engine
{
    std::cout << std::endl; //??
    
    std::string s = str;        // temp string
    std::list<std::string> lst; // temp list
    
    // PRELIMINARY CHECKS
    ///=======================================================
    if(s.empty()) 
    {
      std::cout << "ERROR: empty string" << std::endl; 
      return 0;
    }
    else if(!isBalanced(s))
    {
      std::cout << "ERROR: incorrect syntax : \"(), {}, [], <>\"" << std::endl; 
      return 0;
    } 
    ///=======================================================
    
    // REMOVE LEAD/TAIL WHITESPACE
    ///=======================================================
    s = trimSpace(s); 
    ///=======================================================
        
    //START
    std::cout << "PARSE\n" << "\"" << s << "\"" << std::endl << std::endl;
    std::cout << "PART1\n" << "\"" << s << "\"" << std::endl << std::endl;
    
    // PARSE '.'
    ///=======================================================
    s = par_dot(s);
    ///=======================================================
    
    std::cout << std::endl << "PART2\n" << "\"" << s << "\"" << std::endl << std::endl;      
    
    // PARSE ':'
    ///=======================================================
    par_colon(s,lst);
    
    // print last step through
    std::cout << "step through" << std::endl;
    for(std::list<std::string>::iterator it = lst.begin(); it != lst.end(); it++)
    {
        std::cout << "\"" << *it << "\""  << ", ";
    }
    std::cout << std::endl << std::endl;
    ///=======================================================
    
    std::cout << "PART3" << std::endl;
    
    // construct a list of token objects && substitute variables from Memory
    ///======================================================================
    Object* ob = 0;
    std::list<Object*> oblist;
    
    for(std::list<std::string>::iterator it = lst.begin(); it != lst.end(); it++)
    {
        if( (*it).empty() || *it == "" ) // error check
        {
            std::cout << "ERROR: null string for build object" << std::endl;
            return 0;
        }

        if(*it == ":") // make colon object
        {
            std::cout << "colon part: " << *it << std::endl;
        	ob = new Colon(*it);
        	oblist.push_back(ob);
        	ob = 0;
            continue; 
        }

    	ob = m->goGet(*it); // look for variable||function object in memory hashes
        if(ob != 0)
        {
            std::cout << "mem_variable part: " << *it << std::endl;
        	oblist.push_back(ob);
            ob = 0;
            continue;
        }
        else // make new object
        {
            // code from syscom.cpp modified
            /////////////////////////////////////////////////////////////////////
            std::string val = *it;
            if( val.at(0) == '(' && val.at(val.size()-1) == ')' )
            {
                std::cout << "block part: " << val << std::endl;
                
                // remove ()
                val = val.substr(1, (val.size() - 1)); // gone (
                val = val.substr(0, (val.size() - 1)); // gone )
                ob  = new Block(val);
                oblist.push_back(ob);
                ob = 0;
                continue;
            }
            else if(val.at(0) == '<' && val.at(val.size() - 1) == '>' ) // sequence || element
            {    
                std::cout << "variable part: " << val << std::endl;
                std::list<int> lst;
                
                // remove <>
                val = val.substr(1, (val.size() - 1)); // gone <
                val = val.substr(0, (val.size() - 1)); // gone >
                
                val = trimSpace(val);        
                
                // add empty list HERE 
                if(val.empty())
                {
                    ob = new Sequence(lst);
                    oblist.push_back(ob);
                    ob = 0;
                    continue;
                }
                
                // remove bad junk before segfault
                while( !isalnum(val.at(0)) && val.size() >= 1 )
                {
                    if(val.size() == 1){val = ""; break;}
                    val = val.substr(1, (val.size() - 1));
                } 
                
                // add empty list HERE 
                if(val.empty())
                {
                    ob = new Sequence(lst);
                    oblist.push_back(ob);
                    ob = 0;
                    continue;
                }             
                                
                // extract && store the elements of the sequence    
                char* copy = (char*)(val.c_str());  // copy to give strtok for parse    
                char* arr = strtok(copy, ",");      // temp array      
                lst.push_back( atoi( arr ) );		// add

                for(unsigned i = 1; arr != 0; i++)
                {
                    arr = strtok(NULL, ",");          
                    if(arr)
                    {   
                        lst.push_back( atoi( arr ) );
                    }
                } 

                if(lst.size() == 1)
                {
                    ob = new Element(*lst.begin()); // element HERE
                    oblist.push_back(ob);
                    ob = 0;
                }
                else
                {
                    ob = new Sequence(lst);         // list with data HERE
                    oblist.push_back(ob);
                    ob = 0;
                }
            }
            else // function
            {   
                std::cout << "Function part: " << val << std::endl;
                ob = new Function(val);
                oblist.push_back(ob); 
                ob = 0;       
            }
            ///////////////////////////////////////////////////////////////////////
            // end make object

        } // end if

    } // end for
    ///===========================================================================
    
    // pointer clean
    ob = 0;
    delete ob;

    std::cout << std::endl << "checking:" << std::endl;
    for(std::list<Object*>::iterator it = oblist.begin(); it != oblist.end(); it++)
    {
        std::cout << (*it)->type() << " ";
    	(*it)->print(); 
    	std::cout << std::endl;
    }

    // PART 4    
    // reorder tokens infix to postfix
    oblist = postfix(oblist);

    std::cout << std::endl << "postfixed:" << std::endl;
    for(std::list<Object*>::iterator it = oblist.begin(); it != oblist.end(); it++)
    {
        //std::cout << (*it)->type() << " ";
    	std::cout << "\""; (*it)->print(); std::cout << "\", ";	
    }
    std::cout << std::endl;
    
    // PART 5
    // construct the tree
    std::cout << "buildtree: " << std::endl;
    Node* n = buildtree(oblist, m);
        
    return n;  
}
//-------------------------------------------------------------------------------------------


bool Interpreter::isBalanced(std::string s) // check for ballanced number of separators (), {}, [], <>
{
    std::stack<char> ppp;
    
    for(std::string::iterator it = s.begin(); it != s.end(); it++)
    {
        if( *it == '(' || *it == '[' || *it == '{' || *it == '<')
        {
            ppp.push(*it);
        }
        else if( *it == ')' || *it == ']' || *it == '}' || *it == '>')
        {
            if( ppp.empty() )
            {
                return false;
            }
            else
            {
                if( *it == ')' && ppp.top() != '(' )
                {
                    return false;
                }
                else if( *it == ']' && ppp.top() != '[' )
                {
                    return false;
                }
                else if( *it == '}' && ppp.top() != '{' )
                {
                    return false;
                }
                else if( *it == '>' && ppp.top() != '<' )
                {
                    return false;
                }
                else
                {
                    ppp.pop();
                }
            } 
        }
    }
    
    return ppp.empty();
}
//-------------------------------------------------------------------------------------------


std::string Interpreter::trimSpace(std::string s) // removes any (leading || trailing) whitespace characters
{
    if(s.empty()){return s;}
    while(s.at(0) == ' ') // remove any forward spaces
    {
        if(s.size() == 1 && s.at(0) == ' '){return "";}
        s = s.substr(1, (s.size()-1));
    }
    while(s.at(s.size()-1) == ' ') // remove any trailing spaces
    {
        if(s.size() == 1 && s.at(0) == ' '){return "";}
        s = s.substr(0, (s.size()-1));
    }
    return s;
}
//----------------------------------------------------------------------------------------------


std::string Interpreter::par_dot(std::string& s)    // rewrite (f.g):x -> f:(g:x)
{
    std::cout << "p_dot" << std::endl;
    std::cout << s << std::endl;
    
    std::size_t pos = s.find_last_of('.');
    
    if(pos != std::string::npos && pos < s.size())
    {
        std::string temp = s.substr(0,pos); // all string until '.'
        temp += ":(";
        temp += s.substr(pos+1, s.size()-1);
        temp += ")";
        s = temp;
        
        std::cout << s << std::endl;
        
        par_dot(s);
    }
    
    return s;
}
//------------------------------------------------------------------


void Interpreter::par_colon(std::string& s, std::list<std::string>& lst)
{
    std::cout << "p_col" << std::endl;
    
    std::size_t pos = s.find(":"); // position of first :
    
    if( pos != std::string::npos && pos < s.size() )
    {
        std::string left = s.substr(0, pos); // left half
        left = trimSpace(left); // REMOVE LEAD/TAIL WHITESPACE
        
        lst.push_back(left);  
        lst.push_back(":");
        
        s = s.substr(pos+1);
        
        lst.push_back(s);
        return; // ?
        
    }
    else
    {
        s = trimSpace(s); // REMOVE LEAD/TAIL WHITESPACE
        lst.push_back(s);
        return;
    }

}
//-----------------------------------------------------------------


std::list<Object*> Interpreter::postfix(std::list<Object*> lst) // convert from infix to postfix
{
    std::stack<Object*> s;
    std::list<Object*> pfix;

    std::list<Object*>::iterator it = lst.begin();
    while(it != lst.end())
    {
        if((*it)->type() == "Function"|| (*it)->type() == "Sequence" || (*it)->type() == "Element" || (*it)->type() == "Block")
        {
            pfix.push_back(*it);
        }
        else
        {
            if(s.empty())
            {
                s.push(*it);
            }
            else
            {
                while(!s.empty())
                {
                    pfix.push_back(s.top());
                    s.pop();
                }
                s.push(*it);
            }
        }
        it++;
    }
    
    while(!s.empty())
    {
        pfix.push_back(s.top());
        s.pop();
    }
    
    return pfix;
}
//------------------------------------------------------------------

Node* Interpreter::buildtree(std::list<Object*> lst, Memory* m) // build the AST recursively
{
    std::stack<Node*> s;
    Node* n; // center
    Node* r; // right
    Node* l; // left
    
    for(std::list<Object*>::iterator i = lst.begin(); i != lst.end(); i++)
    {
		if((*i)->type() == "Block") // recursive parse***
        {
        	std::cout << "bt: case1" << std::endl;
        	std::string xstr = (*i)->get()->stringify();
            n = parse(xstr, m);
            s.push(n);
        }
        else if( (*i)->type() == "Function"|| (*i)->type() == "Sequence" || (*i)->type() == "Element" )
        {
        	std::cout << "bt: case2 " << (*i)->type() << std::endl;
            n = new Node((*i)->get());
            s.push(n);
        }
        else // Colon
        {
        	std::cout << "bt: case3 " << (*i)->type() << std::endl;
            if(!s.empty()) // empty == do nothing
            {
                n = new Node((*i)->get());
                if(s.size() >= 2)
                {
                    r = s.top();
                    s.pop();
                    n->setRight(r);
                    r->setParent(n);

                    l = s.top();
                    s.pop();
                    n->setLeft(l);
                    l->setParent(n);
                    
                    s.push(n);
                }
            }
        }
    }
    
    n = s.top();
    s.pop();
    
    return n;
}
//------------------------------------------------------------------
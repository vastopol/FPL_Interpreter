#include "../header/interpreter.h"


Interpreter::~Interpreter()
{
    //  std::cout << "INTERPRETER DESTRUCTOR" << std::endl;
}
//------------------------------------------------

Node* Interpreter::parse(std::string str, Memory* m) // parse engine
{
    std::cout << std::endl;
    
    std::string s = str;        // temp string
    std::list<std::string> lst; // temp list
    
    // PRELIMINARY CHECKS
    ///*******************************************************
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
    ///*******************************************************
    
    // REMOVE LEAD/TAIL WHITESPACE
    ///*******************************************************
    s = trimSpace(s); 
    ///*******************************************************
        
    //START
    std::cout << "PARSE\n" << "\"" << s << "\"" << std::endl << std::endl;
    
    std::cout << "PART1\n" << "\"" << s << "\"" << std::endl << std::endl;
    // PARSE '.'
    ///*******************************************************
    s = par_dot(s);
    ///*******************************************************
    
    std::cout << std::endl << "PART2\n" << "\"" << s << "\"" << std::endl << std::endl;      
    // PARSE ':'
    ///*******************************************************
    par_colon(s,lst);
    
    // print last step through
    std::cout << "step through" << std::endl;
    for(std::list<std::string>::iterator it = lst.begin(); it != lst.end(); it++)
    {
        std::cout << "\"" << *it << "\""  << ", ";
    }
    std::cout << std::endl << std::endl;
    ///*******************************************************
    
    std::cout << "PART3" << std::endl << "not done\n" << std::endl;
    
    // construct a list of token objects && substitute variables from Memory
    
    std::list<Object*> oblist;
    Object* ob = 0;
    
    for(std::list<std::string>::iterator it = lst.begin(); it != lst.end(); it++)
    {
        // if CAPS is function
        // if lower is variable, if number is element, if <> is sequence
        // if ':' make colon object
        
        // if( (it->at(0) == '(') && (it->at(it->size()-1) == ')') ) // block object
        // {
        //     *it = it->substr(1, (it->size() - 1)); // gone )
        //     *it = it->substr(0, (it->size() - 1)); // gone (
        // }

        if(*it == ":")
        {
        	ob = new Colon(*it);
        	oblist.push_back(ob);
        	ob = 0;
        	continue;
        }

    	ob = m->goGet(*it);
        if(ob != 0)
        {
        	oblist.push_back(ob);
        }
    }
    
    for(std::list<Object*>::iterator it = oblist.begin(); it != oblist.end(); it++)
    {
    	(*it)->print(); std::cout << std::endl;
    }

    // PART 4    
    // reorder tokens infix to postfix
    
    // PART 5
    // construct the tree
        
    return 0;  
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



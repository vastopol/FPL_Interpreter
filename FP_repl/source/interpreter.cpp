#include "../header/interpreter.h"


Interpreter::~Interpreter()
{
    //  std::cout << "INTERPRETER DESTRUCTOR" << std::endl;
}
//------------------------------------------------

Node* Interpreter::parse(std::string str, Memory* m) // evaluation engine
{
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
    
    // REMOVE LEAD/TAIL WHITESPACE
    s = trimSpace(s); 
    ///*******************************************************
    
    //START
    std::cout << "string: \"" << s << "\"" << std::endl;
            
    // PARSE ':'
    ///*******************************************************
    while( !s.empty() )
    {
        std::size_t pos = s.find(":"); // position of first :
        
        if( pos != std::string::npos && pos < s.size() )
        {
            std::string left = s.substr(0, pos); // left half
            left = trimSpace(left); // REMOVE LEAD/TAIL WHITESPACE
            lst.push_back(left);  
            lst.push_back(":");
            s = s.substr(pos+1);
        }
        else
        {
            s = trimSpace(s); // REMOVE LEAD/TAIL WHITESPACE
            lst.push_back(s);
            break;
        }
    }
    ///*******************************************************
    
    for(std::list<std::string>::iterator it = lst.begin(); it != lst.end(); it++)
    {
        std::cout << "\'" << *it << "\'"  << ", ";
    }
    std::cout << '\n';
    
    // construct a vector/list of token objects
    // substitute variables from Memeory

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


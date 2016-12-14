#include "../header/interpreter.h"


Interpreter::~Interpreter()
{}
//------------------------------------------------

Node* Interpreter::parse(std::string str, Memory* m) // evaluation engine
{
    std::string s = str;        // temp string
    std::list<std::string> lst; // temp list
    
    //PRELIMINARY CHECKS
    if(str.empty()) 
    {
      std::cout << "ERROR: empty std::string" << std::endl; 
      return 0;
    }
    else if(!isBalanced(str))
    {
      std::cout << "ERROR: incorrect grammar : \"(), [], {}\"" << std::endl; 
      return 0;
    }
    
    // REMOVE PADDING SPACES    
    while(s.at(s.size()-1) == ' ') // remove any trailing spaces
    {
        s = s.substr(0, (s.size()-1));
    }
    while(s.at(0) == ' ') // remove any forward spaces
    {
        s = s.substr(1, (s.size()-1));
    }

    //START
    std::cout << "s: " << s << std::endl;
        
    // PARSE ':'
    ///*******************************************************
    while( !s.empty() )
    {
        std::size_t pos = s.find(":"); // position of first :
        
        if (pos != std::string::npos && pos < s.size() )
        {
            lst.push_back(s.substr(0, pos)); // left half
            lst.push_back(":");
            s = s.substr(pos+1);
        }
        else
        {
            lst.push_back(s);
            break;
        }
    }
    ///*******************************************************
    
    for(std::list<std::string>::iterator it = lst.begin(); it != lst.end(); it++)
    {
        std::cout << *it << ", ";
    }
    std::cout << '\n';
    
    // substitute variables from M

return 0;  
}
//-------------------------------------------------------------------------------------------


bool Interpreter::isBalanced(std::string s) // check for ballanced number of separators (, {, [
{
    std::stack<char> ppp;
    
    for(std::string::iterator it = s.begin(); it != s.end(); it++)
    {
        if(*it == '(' || *it == '[' || *it == '{')
        {
            ppp.push(*it);
        }
        else if(*it == ')' || *it == ']' || *it == '}')
        {
            if(ppp.empty())
            {
                return false;
            }
            else
            {
                if(*it == ')' && ppp.top() != '(' )
                {
                    return false;
                }
                else if(*it == ']' && ppp.top() != '[' )
                {
                    return false;
                }
                else if(*it == '}' && ppp.top() != '{' )
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



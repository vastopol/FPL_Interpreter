#include "interpreter.h"


bool parse(std::string str) // evaluation engine
{
    //PRELIMINARY CHECKS
    if(str.empty()) 
    {
      std::cout << "ERROR: empty std::string" << std::endl; 
      return false;
    }
    else if(!isBalanced(str))
    {
      std::cout << "ERROR: incorrect grammar : \"(), [], {}\"" << std::endl; 
      return false;
    }
    
    std::string s = str; // std::string to modify so original is intact
    
    while(s.at(s.size()-1) == ' ') // remove any trailing spaces
    {
        s = s.substr(0, (s.size()-1));
    }
    

    std::cout << "Parse is unfinished" << std::endl;
    // parse on s
    
    
    
return false;  
}
//-------------------------------------------------------------------------------------------


bool isBalanced(std::string s) // check for ballanced number of separators (, {, [
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



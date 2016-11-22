#include "parse.h"


bool parse(std::string str) // evaluation engine
{
    //PRELIMINARY CHECKS
    if(str.empty()) 
    {
      cout << "ERROR: empty string" << endl; 
      return false;
    }
    else if(!isBalanced(str))
    {
      cout << "ERROR: incorrect grammar : \"(), [], {}\"" << endl; 
      return false;
    }
    
    std::string s = str; // string to modify so original is intact
    
    while(s.at(s.size()-1) == ' ') // remove any trailing spaces
    {
        s = s.substr(0, (s.size()-1));
    }
    

    cout << "Parse is unfinished" << endl;
    // parse on s
    
    
    
return false;  
}
//-------------------------------------------------------------------------------------------


bool isBalanced(string s) // check for ballanced number of separators (, {, [
{
    stack<char> ppp;
    
    for(string::iterator it = s.begin(); it != s.end(); it++)
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



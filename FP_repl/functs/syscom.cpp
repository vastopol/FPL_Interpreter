#include "syscom.h"

void com(std::string s)
{
    if(s == "exit")
    {
        exit(0);
    }
    else if(s == "clear")
    {
        std::cout << "\033c";
        return;
    }
    else if(s == "help")
    {
        help();
    } 
    else
    {
        
        // the exec function here handle sys coms for memory management
        // handle the unknown command in the exec function
        exec(s);
    }
   
   return;
}
//-------------------------------------------------------------------------------------------


void help()
{
    std::cout << "GENERAL:" << std::endl;
    std::cout << "Enter System commands OR use \"#\" operator to evaluate expressions AND equations." << std::endl;
    std::cout << "Have matching parenthesis and correct syntax and grammar." << std::endl;   //// A = B, A != B, A < B, etc... use only 1 binary evaluator
    std::cout << "Separete distinct sub-pieces with parenthesis." << std::endl;
    std::cout << std::endl;
    
    std::cout << "COMMANDS:" << std::endl;
    std::cout << "help" << " == " << "display help prompt" << std::endl;
    std::cout << "clear" << " == " << "clear the screen contents" << std::endl;
    std::cout << "exit" << " == " << "quit program" << std::endl;
    std::cout << "def" << " == " << "define variable" << std::endl;
    std::cout << "rm" << " == " << "remove variable" << std::endl;
    std::cout << "ls" << " == " << "list all variables" << std::endl;
    std::cout << std::endl;
    
    return;
}
//-------------------------------------------------------------------------------------------

void exec(std::string str) // memory management command manager
{    
    if(str.substr(0, 3) == "def") // Variable Definition
    {        
        // syntax: "def name = var"
        unsigned pos = str.find(" "); // location of first space
        if(pos != 3)
        {
            std::cout << "ERROR1: Syntax" << std::endl;
            return;
        }

        // cut out "def ", now "name = var"
        def( str.substr(4, (str.size() - 4) ));
        return;
    }
    else if(str.substr(0, 2) == "rm")
    {
        // syntax: "rm name"
        unsigned pos = str.find(" "); // location of first space
        if(pos != 2)
        {
            std::cout << "ERROR1: Syntax" << std::endl;
            return;
        }   
        
        // remove the variable
        rem( str.substr(3, (str.size() - 1) ));
        return;
    }
    else if(str.substr(0, 2) == "ls")
    {
        //print all vars
        print();
        return;
    }
    else
    {
        std::cout << "ERROR: Unknown Command" << std::endl;
    }
}
//------------------------------------------------------------------------------------------


void def(std::string s) // definition function
{
    // split out "=" and padding spaces
    //**************************************************
    unsigned pos = s.find(" = "); // location of =
    if(pos >= s.size() || pos == std::string::npos)
    {std::cout << "ERROR2: Syntax" << std::endl; return;}
            
    std::string var = s.substr(0, (pos + 1)); // variable name, left half; sz = pos + 1
    if(var.empty()){std::cout << "ERROR3: Syntax -> var" << std::endl; return;}
    
    pos = s.find_last_of(" "); // location of last " "
    if(pos >= s.size() || pos == std::string::npos)
    {std::cout << "ERROR4: Syntax" << std::endl; return;}
    
    std::string val = s.substr((pos + 1), (s.size() - pos)); // variable value, right half
    if(val.empty()){std::cout << "ERROR5: Syntax -> val" << std::endl; return;}
    //*****************************************************
    
    // hash here
    //**************************************************************
    if(val.at(0) == '{' && val.at(val.size() - 1) == '}' ) // sequence
    {
        std::cout << "Sequence: " << std::endl;
        
        std::list<std::string> ls;
        
        val = val.substr(1, (val.size() - 1)); // gone {
        val = val.substr(0, (val.size() - 1)); // gone }
        if(val.empty()){std::cout << "ERROR6: Def of Empty seq.\nfigure out: Push null list later" << std::endl; return;}
        
        
        char* copy = (char*)(val.c_str());      // copy to give strtok for parse
        char* arr = 0;                          // temp array
        
        // extract && store the elements of the sequence        
        arr = strtok(copy, ",");
        ls.push_back(std::string(arr));
        for(unsigned i = 1; arr != 0; i++)
        {
            arr = strtok(NULL, ",");
            if(arr)
            {
                ls.push_back(std::string(arr));
            }
        } 
        
        // hash here #1
        
        // parse check, print list
        for(std::list<std::string>::iterator it = ls.begin(); it != ls.end(); it++)
        {
            std::cout << *it << ", ";
        }
        std::cout << std::endl;
        
    }
    else // element
    {
        std::cout << "element: " << std::endl;
        std::cout << var << std::endl;        
        std::cout << val << std::endl;
        
        // hash here #2
    }
    //******************************************************************************
    
}
//-----------------------------------------------------------------------------------------

void rem(std::string s) // access hashes and remove var if found
{
    if(s.empty())
    {
        std::cout << "ERROR: empty var name" << std::endl;
        return;
    }
    
    std::cout << s << std::endl;
    std::cout << "FIXME: rem" << std::endl;
}
//------------------------------------------------------------------------------------------

void print() // print element hash, print list hash
{
    std::cout << "FIXME: print function" << std::endl;
}
//------------------------------------------------------------------------------------------

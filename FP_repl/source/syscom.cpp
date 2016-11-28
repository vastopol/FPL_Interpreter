#include "../header/syscom.h"
#include "../header/memory.h"

void com(std::string str, Memory* m)
{
    if(str == "exit")
    {
        exit(0);
    }
    else if(str == "clear")
    {
        std::cout << "\033c";
        return;
    }
    else if(str == "help")
    {
        help();
    } 
    else // handle sys coms for memory management
    {
        if(str.substr(0, 3) == "def") // Variable Definition
        {        
            // syntax: "def name = var"
            if(str.find(" ") != 3) // location of first space
            {
                std::cout << "ERROR1: Syntax" << std::endl;
                return;
            }
    
            // cut out "def ", now "name = var"
            def( str.substr(4, (str.size()-4)), m );
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
            rem( str.substr(3, (str.size()-1)), m ); // pass name
            return;
        }
        else if(str.substr(0, 2) == "ls")
        {
            // print all vars
            print(m);
            return;
        }
        else
        {
            std::cout << "ERROR: Unknown Command" << std::endl;
        }
    }
   
   return;
}
//-------------------------------------------------------------------------------------------


void def(std::string s, Memory* m) // definition function
{
    // string s comes in as "name = value" format
    // split out " = ", the equals and padding spaces
    // string var = name; string val = value
    //**************************************************
    unsigned pos = s.find(" = "); // location of =
    if(pos >= s.size() || pos == std::string::npos)
    {std::cout << "ERROR2: Syntax" << std::endl; return;}
            
    std::string var = s.substr(0, (pos)); // variable name, left half; sz = (0 to pos)
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
        std::list<int> lst;
        
        // remove {}
        val = val.substr(1, (val.size() - 1)); // gone {
        val = val.substr(0, (val.size() - 1)); // gone }
        
        // empty list push
        if(val.empty()){m -> add_sequence(var, lst); return;}
        
        char* copy = (char*)(val.c_str());      // copy to give strtok for parse
        char* arr = 0;                          // temp array
        
        // extract && store the elements of the sequence        
        arr = strtok(copy, ",");
        lst.push_back( atoi(arr) );
        for(unsigned i = 1; arr != 0; i++)
        {
            arr = strtok(NULL, ",");
            if(arr)
            {
                lst.push_back( atoi(arr) );
            }
        } 
        
        m -> add_sequence( var, lst ); 
    }
    else // element
    {
        m -> add_element( var, atoi(val.c_str()) );        
    }
    //******************************************************************************
    
}
//-----------------------------------------------------------------------------------------

void rem(std::string s, Memory* m) // access hashes and remove var if found
{
    if(s.empty())
    {
        std::cout << "ERROR: empty var name" << std::endl;
        return;
    }
    m -> remove_element(s);
    m -> remove_sequence(s);
}
//------------------------------------------------------------------------------------------

void print(Memory* m) // print element hash, print list hash
{
    std::cout << "Currently Defined Variables" << std::endl;
    std::cout << "Elements:" << std::endl;
    m -> print_elements();
    std::cout << "Sequences:" << std::endl;    
    m -> print_sequences();
}
//------------------------------------------------------------------------------------------


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
}
//-------------------------------------------------------------------------------------------
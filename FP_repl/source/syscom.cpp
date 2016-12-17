#include "../header/syscom.h"
#include "../header/memory.h"
#include "../header/pattern.h" // for process function


void process(std::string s, Memory* m) // decide if SYSCOM || FP_EXPRESSION -> interpreter
{
    // REMOVE PADDING SPACES
    ///******************************************************************
    while(s.at(0) == ' ') // remove any forward spaces
    {
        s = s.substr(1, (s.size()-1));
    }
    while(s.at(s.size()-1) == ' ') // remove any trailing spaces
    {
        s = s.substr(0, (s.size()-1));
    }
    ///******************************************************************

    // if starts with "#" parse, generate expression tree, execute on root of tree
    if(s.at(0) == '#') 
    {
        s = s.substr(1, s.size()-1); // s now cut out "#"
        Pattern* P = new Pattern(s);         // construct pattern with
        
        // PARSE
        try
        {
            P -> setRoot( P -> getI() -> parse(s, m) );
        }
        catch(std::exception &e)
        {
            std::cout << "ERROR: Parse" << std::endl;
            std::cout << e.what() << std::endl;
        }
        
        // EXECUTE
        try
        {
            P -> getA() -> exec( P -> getRoot() );
        }
        catch(std::exception &e)
        {
            std::cout << "ERROR: Execute" << std::endl;
            std::cout << e.what() << std::endl;
        }
    }   
    else 
    {
        com(s, m); // call COM() for syscommands && memory interaction
    } 
}
//---------------------------------------------------------------------------------

void com(std::string str, Memory* m)
{
    if(str.substr(0, 4) == "exit")
    {
        exit(0);
    }
    else if(str.substr(0, 5) == "clear")
    {
        std::cout << "\033c";
    }
    else if(str.substr(0, 4) == "help")
    {
        help();
    } 
    else // handle sys coms for memory management
    {
        if(str.substr(0, 3) == "let") // Variable creation
        {        
            // syntax: "let name = var"
            if(str.find(" ") != 3) // location of first space
            { std::cout << "ERROR1: Syntax\n"; return; }
    
            // cut out "let ", now "name = var"
            let( str.substr(4, (str.size()-4)), m );
        }
        else if(str.substr(0, 3) == "def") // Function Creation
        {        
            // syntax: "def name = fun"
            if(str.find(" ") != 3) // location of first space
            { std::cout << "ERROR1: Syntax\n"; return; }
    
            // cut out "def ", now "name = fun"
            def( str.substr(4, (str.size()-4)), m );
        }
        else if(str.substr(0, 2) == "rm")
        {
            // syntax: rm name
            if(str.find(" ") != 2) // location of first space
            { std::cout << "ERROR1: Syntax\n"; return; }   
            
            // remove the variable
            rem( str.substr(3, (str.size()-1)), m ); // pass name
        }
        else if(str.substr(0, 4) == "dump")
        {
            dump(m); // clear all memory content
        }
        else if(str.substr(0, 2) == "ls")
        {
            print(m); // print all memory content
        }
        else if(str.substr(0, 4) == "load") // load script content from file
        {        
            // syntax: load "file.fps"
            if(str.find(" ") != 4) // location of first space
            { std::cout << "ERROR1: Syntax\n"; return; }
    
            // cut out load, now "file.fsp"
            load( str.substr(4, (str.size()-1)), m );
        }
        else if(str.substr(0, 3) == "run")
        {
            run(m); // print all memory content
        }
        else
        {
            std::cout << "ERROR: Unknown Command" << std::endl;
        }
    }
    
    return; // catch breakouts
}
//-------------------------------------------------------------------------------------------

void help()
{
    std::cout << std::endl;
    std::cout << "GENERAL:" << std::endl;
    std::cout << "Enter System commands OR use \"#\" operator to evaluate expressions AND equations." << std::endl;
    std::cout << "Have matching parenthesis and correct syntax and grammar." << std::endl;   //// A = B, A != B, A < B, etc... use only 1 binary evaluator
    std::cout << "Separete distinct sub-pieces with parenthesis." << std::endl;
    std::cout << "For more detailed information see: DOCS/syntax.dat || DOCS/technical.dat" << std::endl;
    std::cout << std::endl;
    
    std::cout << "SYSTEM COMMANDS:" << std::endl;
    std::cout << "help" << " == " << "display help prompt" << std::endl;
    std::cout << "clear" << " == " << "clear the screen contents" << std::endl;
    std::cout << "exit" << " == " << "quit program" << std::endl;
    std::cout << "let" << " == " << "create variable" << std::endl;
    std::cout << "def" << " == " << "define function macro" << std::endl;
    std::cout << "rm" << " == " << "remove from memory" << std::endl;
    std::cout << "dump" << " == " << "empty all memory" << std::endl;
    std::cout << "ls" << " == " << "list all memory" << std::endl;
    std::cout << "load" << " == " << "load script to memory buffer" << std::endl;
    std::cout << "run" << " == " << "execute content of memory buffer" << std::endl;
    std::cout << std::endl;
}
//-------------------------------------------------------------------------------------------

void let(std::string s, Memory* m) // variable creation
{
    // string s comes in as "name = value" format
    // split out " = ", the equals and padding spaces
    // string var = name; string val = value
    //**************************************************
    unsigned pos = s.find(" = "); // location of =
    if(pos >= s.size() || pos == std::string::npos)
    { std::cout << "ERROR2: Syntax\n"; return; }
            
    std::string var = s.substr(0, (pos)); // variable name, left half; sz = (0 to pos)
    if(var.empty()){ std::cout << "ERROR3: Syntax -> var\n"; return; }
    
    pos = s.find_last_of(" "); // location of last " "
    if(pos >= s.size() || pos == std::string::npos)
    { std::cout << "ERROR4: Syntax\n"; return; }
    
    std::string val = s.substr((pos + 1), (s.size() - pos)); // variable value, right half
    if(val.empty()){ std::cout << "ERROR5: Syntax -> val\n"; return; }
    //*****************************************************
    
    // hash here
    //**************************************************************
    if(val.at(0) == '<' && val.at(val.size() - 1) == '>' ) // sequence
    {    
        std::list<int> lst;
        
        // remove {}
        val = val.substr(1, (val.size() - 1)); // gone {
        val = val.substr(0, (val.size() - 1)); // gone }
        
        // add empty list HERE
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

void def(std::string s, Memory* m) //  function macro definition
{
    // string s comes in as "name = value" format
    // split out " = ", the equals and padding spaces
    // string var = name; string val = value
    //**************************************************
    unsigned pos = s.find(" = "); // location of =
    if(pos >= s.size() || pos == std::string::npos)
    {std::cout << "ERROR2: Syntax\n"; return;}
            
    std::string var = s.substr(0, (pos)); // variable name, left half; sz = (0 to pos)
    if(var.empty()){std::cout << "ERROR3: Syntax -> var\n"; return;}
    
    pos = s.find_last_of(" "); // location of last " "
    if(pos >= s.size() || pos == std::string::npos)
    { std::cout << "ERROR4: Syntax" << std::endl; return; }
    
    std::string val = s.substr((pos + 1), (s.size() - pos)); // variable value, right half
    if(val.empty()){ std::cout << "ERROR5: Syntax -> val\n"; return; }
    
    m -> add_macro(var, val);
}
//-----------------------------------------------------------------------------------------

void rem(std::string s, Memory* m) // access hashes and remove var if found
{
    if(s.empty())
    { std::cout << "ERROR: empty var name\n"; return; }
    
    m -> remove_element(s);
    m -> remove_sequence(s);
    m -> remove_macro(s);
}
//------------------------------------------------------------------------------------------

void dump(Memory* m)
{
    m -> clear();
}
//-------------------------------------------------------------------------------------------

void print(Memory* m) // print element hash, print list hash
{
    std::cout << "Current Memory State" << std::endl;
    std::cout << "Buffer: "; 
    m -> print_buf_status();
    std::cout << "Elements:" << std::endl;
    m -> print_elements();
    std::cout << "Sequences:" << std::endl;    
    m -> print_sequences();
    std::cout << "Functions:" << std::endl;    
    m -> print_macros();
}
//------------------------------------------------------------------------------------------

void load(std::string str, Memory* m)
{
    std::cout << "BEGIN LOAD" << std::endl;
    
    std::cout << "File: " << str << std::endl;
    
    for(int i = 0; i < 10; i++)
    {
        m -> add_str_buf( std::string("aaaaaaaaa") ); // TEST LOAD
    }
    
    std::cout << "SUCCESSFUL LOAD" << std::endl;
}
//------------------------------------------------------------------------------------------

void run(Memory* m)
{
    std::list<std::string> lst = m -> get_buffer(); // ptr to buffer in memory
    if( lst.empty() )
    {
        std::cout << "ERROR: EMPTY BUFFER" << std::endl;
        return;
    }
    
    std::cout << "BEGIN RUN" << std::endl;
    
    std::list<std::string>::iterator it = lst.begin();
    for(; it != lst.end(); it = lst.begin() ) // it reset to begin each time
    {
        std::cout << *it << std::endl; // TEST PRINT BUFFER CONTENT
        process(*it, m);
        lst.pop_front();
    }
    
    std::cout << "END RUN" << std::endl;
}
//------------------------------------------------------------------------------------------
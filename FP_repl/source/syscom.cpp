#include "../header/syscom.h"
#include "../header/memory.h"
#include "../header/pattern.h" // for process function

// load
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>


void process(std::string s, Memory* m) /* MASTER CONTROL FUNCTION; decides if SYSCOM || FP_EXPRESSION -> interpreter; psudeo preprocessor  */
{
    //REMOVE COMMENTS '#'
    ///******************************************************************
    s = trimSharp(s);
    if(s.empty()){return;}
    ///******************************************************************
    
    // REMOVE PADDING SPACES
    ///******************************************************************
    s = trimSpace(s);
    if(s.empty()){return;}
    ///******************************************************************
    

    /* if string starts with "%" construct pattern object;
       pattern -> interpreter -> parse(string), generates expression tree;
       pattern -> action -> execute(root); */
    if(s.at(0) == '%') 
    {
        s = s.substr(1, s.size()-1); // s now cut out "%"
        Pattern* P = new Pattern(s); // construct pattern with
        
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
        
        delete P; // free the current pattern on heap
    }   
    else 
    {
        com(s, m); // call COM() for syscommands && memory interaction
    } 
}
//---------------------------------------------------------------------------------

void com(std::string s, Memory* m) // ( {let, def, rm, load}  ALL have string arguments)
{
    if(s == "exit")
    {
        delete m; // delete memory object??
        exit(0);
    }
    else if(s == "clear")
    {
        std::cout << "\033c";
    }
    else if(s == "help")
    {
        help();
    } 
    else // handle sys coms for memory management
    {
        if(s.substr(0, 3) == "let") // Variable creation
        {        
            // syntax: "let name = var"
            if(s.find(" ") != 3) // location of first space
            { std::cout << "ERROR1: Syntax\n"; return; }
    
            // cut out "let ", now "name = var"
            let( s.substr(4, (s.size()-4)), m );
        }
        else if(s.substr(0, 3) == "def") // Function Creation
        {        
            // syntax: "def name = fun"
            if(s.find(" ") != 3) // location of first space
            { std::cout << "ERROR1: Syntax\n"; return; }
    
            // cut out "def ", now "name = fun"
            def( s.substr(4, (s.size()-4)), m );
        }
        else if(s.substr(0, 2) == "rm")
        {
            // syntax: rm name
            if(s.find(" ") != 2) // location of first space
            { std::cout << "ERROR1: Syntax\n"; return; }   
            
            // remove the variable
            rem( s.substr(3, (s.size()-1)), m ); // pass name
        }
        else if(s == "dump")
        {
            dump(m); // clear all memory content
        }
        else if(s == "ls")
        {
            print(m); // print all memory content
        }
        else if(s == "bufdump")
        {
            bufdump(m); // clear all buffer content
        }
        else if(s == "bufls")
        {
            bufprint(m); // print all buffer content
        }
        else if(s.substr(0, 4) == "load") // load script content from file to buffer
        {        
            // syntax: load "file.fps"
            if(s.find(" ") != 4) // location of first space
            { std::cout << "ERROR1: Syntax\n"; return; }
    
            // cut out "load", now " file.fsp"
            load( s.substr(5, (s.size()-1)), m );
        }
        else if(s == "run")
        {
            run(m); // execute buffer content
        }
        else
        {
            std::cout << "ERROR: Unknown Command: " << "\"" << s << "\"" << std::endl;
        }
    }
    
    return; // catch breakouts
}
//-------------------------------------------------------------------------------------------

void help()
{
    std::cout << std::endl;
    std::cout << "GENERAL:" << std::endl;
    std::cout << "Enter System commands OR use \'%\' operator to evaluate expressions AND equations." << std::endl;
    std::cout << "Have matching parenthesis and correct syntax and grammar." << std::endl;   //// A = B, A != B, A < B, etc... use only 1 binary evaluator
    std::cout << "Separete distinct sub-pieces with parenthesis." << std::endl;
    std::cout << "For more detailed information see folder: FP_REPL/DOCS/" << std::endl;
    std::cout << std::endl;
    
    std::cout << "SYSTEM COMMANDS:" << std::endl;
    std::cout << "help" << " == " << "display help prompt" << std::endl;
    std::cout << "clear" << " == " << "clear the screen contents" << std::endl;
    std::cout << "exit" << " == " << "quit program" << std::endl;
    std::cout << "let" << " == " << "create variable" << std::endl;
    std::cout << "def" << " == " << "define function macro" << std::endl;
    std::cout << "rm" << " == " << "remove from memory" << std::endl;
    std::cout << "dump" << " == " << "empty all memory" << std::endl;
    std::cout << "bufdump" << " == " << "empty all buffer content" << std::endl;
    std::cout << "ls" << " == " << "list all memory" << std::endl;
    std::cout << "bufls" << " == " << "list all buffer content" << std::endl;
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
    var = trimSpace(var);
    if(var.empty()){ std::cout << "ERROR3: Syntax -> var\n"; return; }
    
    pos = s.find_last_of(" "); // location of last " "
    if(pos >= s.size() || pos == std::string::npos)
    { std::cout << "ERROR4: Syntax\n"; return; }
    
    std::string val = s.substr((pos + 1), (s.size() - pos)); // variable value, right half
    val = trimSpace(val);
    if(val.empty()){ std::cout << "ERROR5: Syntax -> val\n"; return; }
    //*****************************************************
    
    // hash here
    //**************************************************************
    if(val.at(0) == '<' && val.at(val.size() - 1) == '>' ) // sequence
    {    
        std::list<int> lst;
        
        // remove <>
        val = val.substr(1, (val.size() - 1)); // gone <
        val = val.substr(0, (val.size() - 1)); // gone >
        
        // add empty list HERE
        if(val.empty()){m -> add_sequence(var, lst); return;}
        
        char* copy = (char*)(val.c_str());      // copy to give strtok for parse
        char* arr = 0;                          // temp array
        
        // extract && store the elements of the sequence        
        arr = strtok(copy, ",");
        lst.push_back( atoi( arr ) );
        for(unsigned i = 1; arr != 0; i++)
        {
            arr = strtok(NULL, ",");
            if(arr)
            {
                lst.push_back( atoi( arr ) );
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
    var = trimSpace(var);
    if(var.empty()){std::cout << "ERROR3: Syntax -> var\n"; return;}
    
    pos = s.find_last_of(" "); // location of last " "
    if(pos >= s.size() || pos == std::string::npos)
    { std::cout << "ERROR4: Syntax" << std::endl; return; }
    
    std::string val = s.substr((pos + 1), (s.size() - pos)); // variable value, right half
    val = trimSpace(val);
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

void bufdump(Memory* m)
{
    m -> empty_buf();
}
//-------------------------------------------------------------------------------------------

void print(Memory* m) // print element hash, print list hash
{
    std::cout << std::endl;
    std::cout << "Buffer: "; 
    m -> print_buf_status();
    std::cout << "Elements:" << std::endl;
    m -> print_elements();
    std::cout << "Sequences:" << std::endl;    
    m -> print_sequences();
    std::cout << "Functions:" << std::endl;    
    m -> print_macros();
    std::cout << std::endl;
}
//------------------------------------------------------------------------------------------

void bufprint(Memory* m) // print element hash, print list hash
{
    std::cout << std::endl;
    std::cout << "START BUFFER { " << std::endl;
    m -> print_buf();
    std::cout << "} END BUFFER" << std::endl;
    std::cout << std::endl;
}
//------------------------------------------------------------------------------------------

void load(std::string str, Memory* m)
{
    // initial checks
    ///*******************************************************************
    if(str.size() < 5)
    {
        std::cout << "ERROR: LOAD: FILE" << std::endl;
        return;
    }
    else if( str.substr(str.find_last_of('.'), str.size()-1) != ".fps")
    {
        std::cout << "ERROR: LOAD: FILE: EXTENTION" << std::endl;
        return;
    }
    else // C call to see if a file exists (mysterious system calls for linux)
    {
        struct stat buf;
        if(stat(str.c_str(), &buf) == 0)
        {
            if( !(S_ISREG (buf.st_mode & S_IFMT)) )
            {
                std::cout << "ERROR: LOAD: FILE NOT EXIST1" << std::endl;
                return;
            }
        }
        else 
        {
            std::cout << "ERROR: LOAD: FILE NOT EXIST2" << std::endl;
            return;
        }
    }
    ///*******************************************************************
    
    std::string temp;
    std::ifstream inFS;
    inFS.open(str.c_str());
    
    if(!inFS.is_open())
    {
        std::cout << "ERROR: FAILURE TO OPEN: " << str << std::endl;
        return;
    }
    else
    {
        while( getline(inFS,temp) )
        {
            temp = trimSharp(temp); if(temp.empty()){continue;} // rm comments
            temp = trimSpace(temp); if(temp.empty()){continue;} // rm pad spaces
            m -> add_str_buf(temp); // LOAD STRINGS
        }
    }
    
    std::cout << "SUCCESSFUL LOAD" << std::endl;
}
//------------------------------------------------------------------------------------------

void run(Memory* m)
{
    std::list<std::string> lst = m -> get_buffer(); // ptr to buffer in memory
    if( lst.empty() )
    {
        std::cout << "ERROR: RUN: EMPTY BUFFER" << std::endl;
        return;
    }
    
    std::cout << std::endl << "BEGIN RUN{";
    
    std::list<std::string>::iterator it = lst.begin();
    for(; it != lst.end(); it = lst.begin() ) // it reset to begin each time
    {
        // std::cout << *it << std::endl; // TEST PRINT
        process(*it, m);
        lst.pop_front();
    }
    
    std::cout << "}END RUN" << std::endl << std::endl;
}
//------------------------------------------------------------------------------------------

std::string trimSpace(std::string s) // removes any (leading || trailing) whitespace characters
{
    while(s.at(0) == ' ') // remove any forward spaces
    {
        s = s.substr(1, (s.size()-1));
    }
    while(s.at(s.size()-1) == ' ') // remove any trailing spaces
    {
        s = s.substr(0, (s.size()-1));
    }
    return s;
}
//----------------------------------------------------------------------------------------------

std::string trimSharp(std::string s) // remove comments
{
    unsigned pos = s.find('#');
    if( pos != std::string::npos && pos < s.size() )
    {
        s = s.substr(0, pos);
    }  
    return s;
}
//----------------------------------------------------------------------------------------------
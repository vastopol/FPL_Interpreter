#include "../header/syscom.h"
#include "../header/memory.h"
#include "../header/pattern.h" // for process function
#include "../header/object.h"

// load
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>

class Object;
class Element;
class Sequence;
class Function;
class Block;
class Colon;

void process(std::string s, Memory* m) /* preprocessing function */
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
    
    com(s,m); // call to syscom || user input
}
//---------------------------------------------------------------------------------

void com(std::string s, Memory* m) // branch statement to choose syscom || parse.
{
    if(s == "exit")
    {
        delete m; // delete memory object
        m = 0; 
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
    else if(s.substr(0,5) == "print")
    {
        print_ln(s,m);
    }
    else if(s.substr(0, 3) == "def") // Function Creation
    {        
        // syntax: "def name = fun"
        if(s.find(" ") != 3) // location of first space
        { std::cout << "ERROR1: Syntax\n"; return; }

        // cut out "def ", now "name = fun"
        def( s.substr(4, (s.size()-4)), m );
    }
    else if(s.substr(0, 3) == "let") // Variable creation
    {        
        // syntax: "let name = var"
        if(s.find(" ") != 3) // location of first space
        { std::cout << "ERROR1: Syntax\n"; return; }

        // cut out "let ", now "name = var"
        let( s.substr(4, (s.size()-4)), m );
    }
    else if(s.substr(0, 3) == "set")
    {
        if(s.find(" ") != 3) // location of first space
        { std::cout << "ERROR1: Syntax\n"; return; }

        set( s.substr(4, (s.size()-4)), m );
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
        dump_mem(m); 
    }
    else if(s == "ls")
    {
        print_mem(m); 
    }
    else if(s == "bufdump")
    {
        dump_buf(m); 
    }
    else if(s == "bufls")
    {
        print_buf(m); 
    }
    else if(s.substr(0, 4) == "load") // load script content from file to buffer
    {        
        // syntax: load "file.fps"
        if(s.find(" ") != 4) // location of first space
        { std::cout << "ERROR1: Syntax\n"; return; }

        // cut out "load", now " file.fsp"
        load( s.substr(5, (s.size()-1)), m );
    }
    else if(s == "run") // execute buffer content
    {
        run(m); 
    }
    else if(s.substr(0,7) == "gentree")
    {
        if(s.find(" ") != 7) // location of first space
        { std::cout << "ERROR1: Syntax\n"; return; }

        gentree(s.substr(8,s.size()-1), m);
    }
    else // try to execute user input
    {
        eval(s,m);
    } 
    
    return; // catch any breakouts
}
//-------------------------------------------------------------------------------------------

void help()
{
    std::cout << std::endl;
    std::cout << "GENERAL:" << std::endl;
    std::cout << "Enter System commands OR evaluate expressions AND equations." << std::endl;
    std::cout << "Have matching parenthesis and correct syntax and grammar." << std::endl;   //// A = B, A != B, A < B, etc... use only 1 binary evaluator
    std::cout << "Separete distinct sub-pieces with parenthesis." << std::endl;
    std::cout << "For more detailed information see folder: FP_repl/DOCS/" << std::endl;
    std::cout << std::endl;
    
    std::cout << "SYSTEM COMMANDS:" << std::endl;
    std::cout << "help" << " == " << "display help prompt" << std::endl;
    std::cout << "clear" << " == " << "clear the screen contents" << std::endl;
    std::cout << "exit" << " == " << "quit program" << std::endl;
    std::cout << "def" << " == " << "define function macro" << std::endl;
    std::cout << "let" << " == " << "create variable" << std::endl;
    std::cout << "set" << " == " << "set a variable to an expression value" << std::endl;
    std::cout << "rm" << " == " << "remove an entry from memory" << std::endl;
    std::cout << "dump" << " == " << "empty all memory" << std::endl;
    std::cout << "bufdump" << " == " << "empty all buffer content" << std::endl;
    std::cout << "ls" << " == " << "list all memory" << std::endl;
    std::cout << "bufls" << " == " << "list all buffer content" << std::endl;
    std::cout << "load" << " == " << "load script to memory buffer" << std::endl;
    std::cout << "run" << " == " << "execute content of memory buffer" << std::endl;
    std::cout << "print" << " == " << "print a string, ends on newline, use $ for variables" << std::endl;
    std::cout << "gentree" << " == " << "parses an expression, generates the AST using graphviz" << std::endl;
    std::cout << std::endl;
}
//-------------------------------------------------------------------------------------------

void def(std::string s, Memory* m) //  function macro definition
{
    // string s comes in as "name = value" format
    // split out " = ", the equals and padding spaces
    // string var = name; string val = value
    //**************************************************
    size_t pos = s.find(" = "); // location of =
    if(pos >= s.size() || pos == std::string::npos)
    {std::cout << "ERROR2: Syntax\n"; return;}
            
    std::string var = s.substr(0, (pos)); // variable name, left half; sz = (0 to pos)
    var = trimSpace(var);
    if(var.empty()){std::cout << "ERROR3: Syntax -> var\n"; return;}
    
    pos = s.find(" "); // location of first " "
    pos = s.find(" ", pos+1); // location of " " right after the "="
    if(pos >= s.size() || pos == std::string::npos)
    { std::cout << "ERROR4: Syntax" << std::endl; return; }
    
    std::string val = s.substr((pos + 1), (s.size() - pos)); // variable value, right half
    val = trimSpace(val);
    if(val.empty()){ std::cout << "ERROR5: Syntax -> val\n"; return; }
    
    Function fun(val);

    m -> add_macro(var, fun);
}
//-----------------------------------------------------------------------------------------

void let(std::string s, Memory* m) // variable creation
{
    // string s comes in as "name = value" format
    // split out " = ", the equals and padding spaces
    // string var = name; string val = value
    //**************************************************
    size_t pos = s.find(" = "); // location of =
    if(pos >= s.size() || pos == std::string::npos)
    { std::cout << "ERROR2: Syntax\n"; return; }
            
    std::string var = s.substr(0, (pos)); // variable name, left half; sz = (0 to pos)
    var = trimSpace(var);
    if(var.empty()){ std::cout << "ERROR3: Syntax -> var\n"; return; }
    
    pos = s.find(" "); // location of first " "
    pos = s.find(" ", pos+1); // location of " " right after the "="
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
        
        val = trimSpace(val);        
        
        // add empty list HERE 
        if(val.empty())
        {
            Sequence seq(lst);
            m -> add_sequence(var, seq); 
            return;
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
            Sequence seq(lst);
            m -> add_sequence(var, seq); 
            return;
        }
        
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

        // add list with data HERE
        Sequence seq(lst);
        m -> add_sequence( var, seq );
    }
    else // element
    {
        Element e(atoi(val.c_str()));
        m -> add_element( var, e );        
    }
    //****************************************************************************** 

}
//-----------------------------------------------------------------------------------------


void set(std::string s, Memory* m) 
{
    // string s comes in as "name = value" format
    // split out " = ", the equals and padding spaces
    // string var = name; string val = value
    //**************************************************
    size_t pos = s.find(" = "); // location of =
    if(pos >= s.size() || pos == std::string::npos)
    {std::cout << "ERROR2: Syntax\n"; return;}
            
    std::string var = s.substr(0, (pos)); // variable name, left half; sz = (0 to pos)
    var = trimSpace(var);
    if(var.empty()){std::cout << "ERROR3: Syntax -> var\n"; return;}
    
    pos = s.find(" "); // location of first " "
    pos = s.find(" ", pos+1); // location of " " right after the "="
    if(pos >= s.size() || pos == std::string::npos)
    { std::cout << "ERROR4: Syntax" << std::endl; return; }
    
    std::string val = s.substr((pos + 1), (s.size() - pos)); // variable value, right half
    val = trimSpace(val);
    if(val.empty()){ std::cout << "ERROR5: Syntax -> val\n"; return; }

    if(m->goGet(var) == 0)
    {
        std::cout << "ERROR: Undefined variable to bind to" << std::endl; return;
    }
    //**************************************************

    Pattern* P = new Pattern(val); // construct pattern with
    Object* obb = 0;

    // PARSE
    try
    {
        P -> setRoot( P -> getI() -> parse(val, m) );
    }
    catch(std::exception &e)
    {
        std::cout << "ERROR: Parse" << std::endl;
        std::cout << e.what() << std::endl;
        delete P; // delete the current pattern on heap
        P = 0;
        return;
    }
    
    // EXECUTE
    try
    {
        obb = P -> getA() -> exec( P -> getRoot() );
        obb->print(); std::cout << std::endl;
    }
    catch(std::exception &e)
    {
        std::cout << "ERROR: Execute" << std::endl;
        std::cout << e.what() << std::endl;
        delete P; // delete the current pattern on heap
        P = 0;  
        delete obb;
        obb = 0;
        return;
    }

    // SET
    if(obb == 0)
    {
        std::cout << "ERROR: Execute produced null" << std::endl; return;
    }
    else if(obb->type() == "Element")
    {
        rem(var,m); // deletes old variable entry
        m->add_element(var, *(static_cast<Element*>(obb)) );
    }
    else if (obb->type() == "Sequence")
    {
        rem(var,m); // deletes old variable entry
        m->add_sequence(var, *(static_cast<Sequence*>(obb)) );
    }
    else
    {
        std::cout << "ERROR: Execute produced an unknown value" << std::endl; return;
    }

    delete P; // delete the current pattern on heap
    P = 0;

    // delete obb; // comment out to fix ERROR #2
    // obb = 0;


// ERROR #1 (appears to be fixed... idk why...)
// setting a variable equal to itself causes an error (probably because of remove and recreate...)
// Error pure virtual method called terminate called without an active exception, Aborted

// ERROR #2 (fixed)
// setting a variable equal to another variable causes an error
// *** Error in `bin/fplr': free(): invalid pointer *** Aborted
}
//-----------------------------------------------------------------------------------------


void rem(std::string s, Memory* m) // access hashes and remove var if found
{
    if(s.empty())
    { std::cout << "ERROR: empty var name\n"; return; }
    
    s = trimSpace(s);
    if(s.empty()){return;}
    
    m -> remove_element(s);
    m -> remove_sequence(s);
    m -> remove_macro(s);
    return;
}
//------------------------------------------------------------------------------------------

void dump_mem(Memory* m)
{
    m -> clear();
    return;
}
//-------------------------------------------------------------------------------------------

void dump_buf(Memory* m)
{
    m -> empty_buf();
    return;
}
//-------------------------------------------------------------------------------------------

void print_mem(Memory* m) // ls
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
    return;
}
//------------------------------------------------------------------------------------------

void print_buf(Memory* m) // bufls
{
    std::cout << std::endl;
    std::cout << "START BUFFER { " << std::endl;
    m -> print_buf();
    std::cout << "} END BUFFER" << std::endl;
    std::cout << std::endl;
    return;
}
//------------------------------------------------------------------------------------------

void print_ln(std::string s, Memory* m)
{
    if(s.size() == 5) // echo \n
    {
        std::cout << std::endl;
        return;
    }

    if(s.find(" ") != 5) // location of first space
    { std::cout << "ERROR1: Syntax\n"; return; } 

    // cut out "print " 
    s = s.substr(6, s.size()-6);

    if(s.at(0) == '$') // print item from mem
    {
        Object* ob = m->goGet(s.substr(1, s.size()-1));
        if(ob != NULL)
        {
            ob->print();
            std::cout << std::endl;
        }
        else
        {
            std::cout << "ERROR: Undefined" << std::endl;
        }

        // delete ob; ob = 0; // ?? ptr management ??
    }
    else // print string
    {
        std::cout << s << std::endl;
    }
    return;
}
//------------------------------------------------------------------------------------------


void gentree(std::string s, Memory* m)   // generate a visual of the AST with Graphviz
{
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
        delete P; // delete the current pattern on heap
        P = 0;
        return;
    }

    // print tree
    P->preOrder(P->getRoot()); std::cout << std::endl;
    P->inOrder(P->getRoot()); std::cout << std::endl;
    P->postOrder(P->getRoot()); std::cout << std::endl;

    // generate tree with graphviz
    P->visualizeTree("output.dot");

    delete P; // delete the current pattern on heap
    P = 0;
    return;
}
//------------------------------------------------------------------------------------------
void eval(std::string s, Memory* m)      // evaluate an expression   
{
    Pattern* P = new Pattern(s); // construct pattern with user input
    
    // PARSE
    try
    {
        P -> setRoot( P -> getI() -> parse(s, m) );
    }
    catch(std::exception &e)
    {
        std::cout << "ERROR: Parse" << std::endl;
        std::cout << e.what() << std::endl;
        delete P; // delete the current pattern on heap
        P = 0;
        return;
    }
    
    // EXECUTE
    try
    {
        Object* obb = P -> getA() -> exec( P -> getRoot() );
        if(obb != 0)
        {
            obb->print(); std::cout << std::endl;
        }
        // delete obb; // comment out to fix ERROR #1
        // obb = 0;    
    }
    catch(std::exception &e)
    {
        std::cout << "ERROR: Execute" << std::endl;
        std::cout << e.what() << std::endl;
    }
    delete P; // delete the current pattern on heap
    P = 0;
    return;

// ERROR #1 (fixed)
// evaluating an element or sequence by itself crashes

}
//------------------------------------------------------------------------------------------

void load(std::string s, Memory* m) // removes comments && trims spaces
{
    // initial checks
    ///*******************************************************************
    s = trimSpace(s);
    if(s.size() < 5)
    {
        std::cout << "ERROR: LOAD: FILE" << std::endl;
        return;
    }
    else if( s.substr(s.find_last_of('.'), s.size()-1) != ".fpl")
    {
        std::cout << "ERROR: LOAD: FILE: EXTENTION" << std::endl;
        return;
    }
    else // C call to see if a file exists (mysterious system calls for linux)
    {
        struct stat buf;
        if(stat(s.c_str(), &buf) == 0)
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
    inFS.open(s.c_str());
    
    if(!inFS.is_open())
    {
        std::cout << "ERROR: FAILURE TO OPEN: " << s << std::endl;
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
    
    inFS.close();
    std::cout << "SUCCESSFUL LOAD" << std::endl;
    return;
}
//------------------------------------------------------------------------------------------

void run(Memory* m)
{
    std::list<std::string>& lst = m -> get_buffer(); // copy buffer from memory, &lst 
    if( lst.empty() )
    {
        std::cout << "ERROR: RUN: EMPTY BUFFER" << std::endl;
        return;
    }
    
    std::cout << std::endl << "BEGIN RUN{";
    
    std::list<std::string>::iterator it = lst.begin();
    for( ; it != lst.end(); it = lst.begin() ) // it reset to begin each time
    {
        process(*it, m);
        if(!lst.empty())
        {
            lst.pop_front();
        }
    }
    
    std::cout << "}END RUN" << std::endl << std::endl;
    return; 
}
//------------------------------------------------------------------------------------------

std::string trimSpace(std::string s) // removes any (leading || trailing) whitespace characters
{
    if(s.empty()){return s;}
    while(s.at(0) == ' ') // remove any forward spaces
    {
        if(s.size() == 1){return "";}
        s = s.substr(1, (s.size()-1));
    }
    while(s.at(s.size()-1) == ' ') // remove any trailing spaces
    {
        if(s.size() == 1){return "";}
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


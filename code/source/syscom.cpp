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

void process(std::string s, Memory* m) // preprocessing using utils functions
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

    m->add_str_hist(s); // save to history the cleaned up command

    com(s,m);           // call to syscom || eval user input
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
    else if(s == "fcts")
    {
        fcts();
    }
    else if(s == "history")
    {
        history(m);
    }
    else if(s == "print" || s.substr(0,6) == "print ")
    {
        print_ln(s,m);
    }
    else if(s.substr(0,6) == "write ")
    {
        write_buf(s,m);
    }
    else if(s == "step")
    {
        step(m);
    }
    else if(s.substr(0, 4) == "def ") // Function Creation
    {
        // syntax: "def name = fun"
        if(s.find(" ") != 3) // location of first space
        { std::cout << "ERROR1: Syntax\n"; return; }

        // cut out "def ", now "name = fun"
        def( s.substr(4, (s.size()-4)), m );
    }
    else if(s.substr(0, 4) == "let ") // Variable creation
    {
        // syntax: "let name = var"
        if(s.find(" ") != 3) // location of first space
        { std::cout << "ERROR1: Syntax\n"; return; }

        // cut out "let ", now "name = var"
        let( s.substr(4, (s.size()-4)), m );
    }
    else if(s.substr(0, 3) == "rm ")
    {
        // syntax: rm name
        if(s.find(" ") != 2) // location of first space
        { std::cout << "ERROR1: Syntax\n"; return; }

        // pass variable name
        rem( s.substr(3, (s.size()-1)), m );
    }
    else if(s == "mem")
    {
        print_mem(m);
    }
    else if(s == "memdump")
    {
        dump_mem(m);
    }
    else if(s == "buf")
    {
        print_buf(m);
    }
    else if(s == "bufdump")
    {
        dump_buf(m);
    }
    else if(s.substr(0, 5) == "load ")
    {
        // syntax: load "file.fpl"
        if(s.find(" ") != 4) // location of first space
        { std::cout << "ERROR1: Syntax\n"; return; }

        // cut out "load", now " file.fpl"
        load( s.substr(5, (s.size()-1)), m );
    }
    else if(s == "run")
    {
        run(m);
    }
    else if(s.substr(0,8) == "gentree ")
    {
        if(s.find(" ") != 7) // location of first space
        { std::cout << "ERROR1: Syntax\n"; return; }

        gentree(s.substr(8,s.size()-1), m);
    }
    else if(s.substr(0,5) == "type ")
    {
        if(s.find(" ") != 4) // location of first space
        { std::cout << "ERROR1: Syntax\n"; return; }

        type(s.substr(5,s.size()-1), m);
    }
    else if(s.substr(0,2) == "! ") // execute an arbitrary command with system() -- DANGER TIME --
    {
        if(s.find(" ") != 1) // location of first space
        { std::cout << "ERROR1: Syntax\n"; return; }

        //std::cout << "CALL SYSTEM" << std::endl;
        int i = system( s.substr(1,s.size()-1).c_str() );
        //std::cout << "RETURN SYSTEM" << std::endl;
        //std::cout << "EXIT STATUS: " << i << std::endl;
    }
    else
    {
        eval(s,m);
    }

    return; // catch any breakouts
}
//-------------------------------------------------------------------------------------------

void help()
{
    std::cout << std::endl;
    std::cout << "HELP DOCUMENT:" << std::endl;
    std::cout << std::endl;
    std::cout << "GENERAL:" << std::endl;
    std::cout << "Enter commands OR evaluate expressions." << std::endl;
    std::cout << std::endl;
    std::cout << "COMMANDS:" << std::endl;
    std::cout << "help    == display help" << std::endl;
    std::cout << "fcts    == display functions" << std::endl;
    std::cout << "history == display history" << std::endl;
    std::cout << "clear   == clear the screen contents" << std::endl;
    std::cout << "exit    == quit program" << std::endl;
    std::cout << "def     == define function macro" << std::endl;
    std::cout << "let     == create/set a variable to an expression value" << std::endl;
    std::cout << "rm      == remove an entry from memory" << std::endl;
    std::cout << "mem     == list all memory" << std::endl;
    std::cout << "buf     == list all buffer content" << std::endl;
    std::cout << "memdump == empty all memory" << std::endl;
    std::cout << "bufdump == empty all buffer content" << std::endl;
    std::cout << "load    == load script to memory buffer" << std::endl;
    std::cout << "run     == execute content of memory buffer" << std::endl;
    std::cout << "step    == execute 1 instruction from memory buffer" << std::endl;
    std::cout << "write   == write line to memory buffer" << std::endl;
    std::cout << "print   == print a string, ends on newline, use $ for variables" << std::endl;
    std::cout << "gentree == parses an expression, generates the AST using graphviz" << std::endl;
    std::cout << "type    == show function or expression type signature" << std::endl;
    std::cout << "!       == execute external shell command with system()" << std::endl;
    std::cout << std::endl;
}
//-------------------------------------------------------------------------------------------

void fcts()
{
    std::cout << std::endl;
    std::cout << "Functions in FPL:" << std::endl;
    std::cout << std::endl;
    std::cout << "ELEMENT OPERATIONS" << std::endl;
    std::cout << std::endl;
    std::cout << "RETURN TYPE (ELEMENT)" << std::endl;
    std::cout << "- neg == negate, take opposite sign of number" << std::endl;
    std::cout << "- abs == take absolute value of number" << std::endl;
    std::cout << "- inc == increment (plus 1)" << std::endl;
    std::cout << "- dec == decrement (minus 1)" << std::endl;
    std::cout << "- square == second power" << std::endl;
    std::cout << "- cube == third power" << std::endl;
    std::cout << "- sqrt == square root" << std::endl;
    std::cout << "- not  == logical not" << std::endl;
    std::cout << "- odd  == test is odd" << std::endl;
    std::cout << "- even == test is even" << std::endl;
    std::cout << "- zero == test is zero" << std::endl;
    std::cout << std::endl;
    std::cout << "RETURN TYPE (SEQUENCE)" << std::endl;
    std::cout << "- intsto  == list from 1 to n" << std::endl;
    std::cout << "- ones    == list of n ones" << std::endl;
    std::cout << "- zeros   == list of n zeros" << std::endl;
    std::cout << "- list    == create a list around an element" << std::endl;
    std::cout << std::endl;
    std::cout << "SEQUENCE OPERATIONS" << std::endl;
    std::cout << std::endl;
    std::cout << "RETURN TYPE (ELEMENT)" << std::endl;
    std::cout << "- head  == first element of sequence" << std::endl;
    std::cout << "- size  == number of elements in list" << std::endl;
    std::cout << "- max  == maximum value in sequence" << std::endl;
    std::cout << "- min  == minimum value in sequence" << std::endl;
    std::cout << "- sum   == add the elements of a sequence together" << std::endl;
    std::cout << "- prod  == multiply the elements of a sequence together" << std::endl;
    std::cout << "- nil   == check for empty list" << std::endl;
    std::cout << "(eq,neq,gt,lt,gte,lte) == act on first 2 elements" << std::endl;
    std::cout << std::endl;
    std::cout << "RETURN TYPE (SEQUENCE)" << std::endl;
    std::cout << "- tail  == sequence from second to end" << std::endl;
    std::cout << "- popl  == pop element from left of sequence" << std::endl;
    std::cout << "- popr  == pop element from right of sequence" << std::endl;
    std::cout << "- rotl  == rotate sequence elements to the left" << std::endl;
    std::cout << "- rotr  == rotate sequence elements to the right" << std::endl;
    std::cout << "- rev   == reverse the order of a sequence" << std::endl;
    std::cout << "- sort  == sort sequence into ascending order" << std::endl;
    std::cout << "- rmdup == remove duplicates, preserves order" << std::endl;
    std::cout << "(+,-,*,/,%) == act on first 2 elements" << std::endl;
    std::cout << std::endl;
    std::cout << "HIGHER ORDER FUNCTIONS/OPERATORS" << std::endl;
    std::cout << std::endl;
    std::cout << "- id   == identity" << std::endl;
    std::cout << "- elm  == check is type Element" << std::endl;
    std::cout << "- seq  == check is type Sequence" << std::endl;
    std::cout << "- map{f}  == apply function f to each element of list" << std::endl;
    std::cout << "- filt{p} == filter elements that fail predicate p from list" << std::endl;
    std::cout << "- at{i}   == get element at index i from list" << std::endl;
    std::cout << "- apr{e}  == append element at right of list" << std::endl;
    std::cout << "- apl{e}  == append element at left of list" << std::endl;
    std::cout << "- cat{l}  == concatenate 2 lists" << std::endl;
    std::cout << "- if{p;f;g}  == if p is true when applied, then f else g" << std::endl;
    std::cout << "- ccf{f1;...;fn}  == list of <f1:x,...,fn:x>" << std::endl;
    std::cout << std::endl;
}
//-------------------------------------------------------------------------------------------

void history(Memory* m)
{
    std::cout << std::endl;
    std::cout << "History: " << std::endl;
    std::cout << std::endl;
    m->print_history();
    std::cout << std::endl;
}

//-------------------------------------------------------------------------------------------

void def(std::string s, Memory* m) //  function macro definition
{
    // string s comes in as "name = value" format
    // split out " = ", the equals and padding spaces
    // string var = name; string val = value
    //**************************************************
    // size_t pos = s.find(" = "); // location of =
    size_t pos = s.find("="); // location of =
    if(pos >= s.size() || pos == std::string::npos)
    {std::cout << "ERROR2: Syntax\n"; return;}

    std::string var = s.substr(0, (pos)); // variable name, left half; sz = (0 to pos)
    var = trimSpace(var);
    if(var.empty()){std::cout << "ERROR3: Syntax -> var\n"; return;}

    // pos = s.find(" ");        // location of first " "
    // pos = s.find(" ", pos+1); // location of " " right after the "="
    // if(pos >= s.size() || pos == std::string::npos)
    // { std::cout << "ERROR4: Syntax" << std::endl; return; }

    std::string val = s.substr((pos + 1), (s.size() - pos)); // variable value, right half
    val = trimSpace(val);
    if(val.empty()){ std::cout << "ERROR5: Syntax -> val\n"; return; }

    Function fun(val);

    m -> add_macro(var, fun);
}
//-----------------------------------------------------------------------------------------

void let(std::string s, Memory* m)
{
    // string s comes in as "name = value" format
    // split out " = ", the equals and padding spaces
    // string var = name; string val = value
    //**************************************************
    // size_t pos = s.find(" = "); // location of =
    size_t pos = s.find("="); // location of =
    if(pos >= s.size() || pos == std::string::npos)
    {std::cout << "ERROR2: Syntax\n"; return;}

    std::string var = s.substr(0, (pos)); // variable name, left half; sz = (0 to pos)
    var = trimSpace(var);
    if(var.empty()){std::cout << "ERROR3: Syntax -> var\n"; return;}

    // pos = s.find(" ");        // location of first " "
    // pos = s.find(" ", pos+1); // location of " " right after the "="
    // if(pos >= s.size() || pos == std::string::npos)
    // { std::cout << "ERROR4: Syntax" << std::endl; return; }

    std::string val = s.substr((pos + 1), (s.size() - pos)); // variable value, right half
    val = trimSpace(val);
    if(val.empty()){ std::cout << "ERROR5: Syntax -> val\n"; return; }

    /*if(m->goGet(var) == 0)
    {
        std::cout << "ERROR: Undefined variable to bind to" << std::endl; return;
    }*/
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
        obb = P -> getA() -> exec( P -> getRoot() , m );
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

void dump_mem(Memory* m) // dump
{
    m -> clear();
    return;
}
//-------------------------------------------------------------------------------------------

void dump_buf(Memory* m) // bufdump
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
    // std::cout << "START BUFFER { " << std::endl;
    m -> print_buffer();
    // std::cout << "} END BUFFER" << std::endl;
    std::cout << std::endl;
    return;
}
//------------------------------------------------------------------------------------------

void print_ln(std::string s, Memory* m) // print
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
    Pattern* P = new Pattern(s); // construct pattern

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

void eval(std::string s, Memory* m)    // evaluate an expression
{
    Pattern* P = new Pattern(s);       // construct pattern with user input

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
        Object* obb = P -> getA() -> exec( P -> getRoot() , m );
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
            m -> add_str_buf(temp);                             // LOAD STRING
        }
    }

    inFS.close();
    std::cout << "SUCCESSFUL LOAD" << std::endl;
    return;
}
//------------------------------------------------------------------------------------------

void run(Memory* m)
{
    std::list<std::string>& lst = m -> get_buffer();    // copy buffer from memory // &lst
    if( lst.empty() )
    {
        std::cout << "ERROR: RUN: EMPTY BUFFER" << std::endl;
        return;
    }

    //std::cout << std::endl << "BEGIN RUN{";

    std::list<std::string>::iterator it = lst.begin();
    for( ; it != lst.end(); it = lst.begin() )          // it reset to begin each time
    {
        process(*it, m);
        if(!lst.empty())
        {
            lst.pop_front();
        }
    }

    //std::cout << "}END RUN" << std::endl << std::endl;
    return;
}
//------------------------------------------------------------------------------------------

void step(Memory* m)                     // execute 1 command form buffer
{
    std::list<std::string>& lst = m -> get_buffer();    // copy buffer from memory // &lst
    if( lst.empty() )
    {
        std::cout << "ERROR: STEP: EMPTY BUFFER" << std::endl;
        return;
    }
    std::string s = lst.front();
    lst.pop_front();
    process(s, m);
    return;
}
//------------------------------------------------------------------------------------------

void write_buf(std::string s, Memory* m) // write 1 line append to buffer
{
    if(s.size() == 5)
    {
        std::cout << "ERROR: WRITE: empty string" << std::endl;
        return;
    }

    if(s.find(" ") != 5) // location of first space
    { std::cout << "ERROR1: Syntax\n"; return; }

    // cut out "write "
    s = s.substr(6, s.size()-6);

    m->add_str_buf(s);

    return;
}
//------------------------------------------------------------------------------------------

void type(std::string s, Memory* m) // type signature
{
    Pattern* P = new Pattern(s); // construct pattern
    std::stack<std::string> type_toks;
    std::string tmp_tok;
    int func_type;

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

    // TRAVERSE
    type_toks = P->postOrderCheckWrap(P->getRoot());

    if(type_toks.empty()){ std::cout << "Error: Type stack is empty" << std::endl; }

    // assume type of first char in string
    // number = int, '<' = list, alpha/symbol = function
    while(!type_toks.empty())
    {
        if(type_toks.top() == ":"){ type_toks.pop(); continue; }
        tmp_tok = type_toks.top();
        type_toks.pop();
        if( isdigit(tmp_tok.at(0)) ) // int
        {
            std::cout << "INT" << std::endl;
        }
        else if(tmp_tok.at(0) == '<') // list
        {
            std::cout << "LIST" << std::endl;
        }
        else // fun/op
        {
            func_type = func_classifier(tmp_tok);

            if(func_type == -1 ) // operator
            {
                if( (tmp_tok.find('{') != std::string::npos) || tmp_tok == "id" || tmp_tok == "seq" || tmp_tok == "elm" )
                {
                    std::cout << "OP:" << std::endl;
                }
                else
                {
                    std::cout << "Error: unknown function type" << std::endl; /*break;*/
                }
            }
            else // function
            {
                std::cout << "FUN: ";
                switch(func_type)
                {
                    case 0:
                        std::cout << "INT  -> INT";
                        break;
                    case 1:
                        std::cout << "INT  -> LIST";
                        break;
                    case 2:
                        std::cout << "LIST -> INT";
                        break;
                    case 3:
                        std::cout << "LIST -> LIST";
                        break;
                    default:
                        std::cout << "Error: unknown function type (in switch)"; // << std::endl; // should never go here because the if above switch
                        // break;
                }
                std::cout << std::endl;
            }
        }
    }

    delete P; // delete the current pattern on heap
    P = 0;
    return;
}

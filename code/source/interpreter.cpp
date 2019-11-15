#include "../header/interpreter.h"

//--------------------------------------------------------------------------------

Interpreter::~Interpreter()
{}
//--------------------------------------------------------------------------------

// parsing engine
Node* Interpreter::parse(std::string str, Memory* m)
{
    std::string s = str;        // temp string
    std::list<std::string> lst; // temp list strings
    std::list<Object*> oblist;  // temp list object pointers

    // preliminary checks
    if(s.empty())
    {
        std::cout << "ERROR: empty string" << std::endl;
        throw std::runtime_error("parse() : empty string in prelim");
    }
    else if(!isBalanced(s))
    {
        std::cout << "ERROR: incorrect syntax : \"(), {}, [], <>\"" << std::endl;
        throw std::runtime_error("parse() : unballanced <,(,{,[");
    }

    // remove whitespace
    s = trimSpace(s);

    // resolve definitions
    s = resolve(s,m);

    // parse '.' composition
    s = par_dot(s);

    // parse ':' application
    par_colon(s,lst);

    // construct a list of token objects &&
    // substitute variables from Memory
    oblist = toklist(lst,m);

    // reorder tokens infix to postfix
    oblist = postfix(oblist);

    // construct the tree
    Node* n = buildtree(oblist, m);

    return n;
}
//--------------------------------------------------------------------------------

// check for ballanced number of separators (), {}, [], <>
bool Interpreter::isBalanced(std::string s)
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
//--------------------------------------------------------------------------------

// resolve all definitions on left to chain of composed primitives
std::string Interpreter::resolve(std::string& s, Memory* m)
{
    std::string left;
    std::string right;
    std::string temp;
    std::queue<std::string> qq;
    Object* ob = 0;
    std::size_t pos = 0;

    pos = s.find(':');
    if(pos == std::string::npos || pos >= s.size())
    {
        return s;
    }

    right = s.substr(pos+1,s.size()-1);
    left = s.substr(0,pos);
    temp = left;
    pos = 0;
    while(pos != std::string::npos || pos >= temp.size())
    {
        std::string zap = "";
        pos = temp.find('.');
        if(pos == std::string::npos || pos >= temp.size()) // lookup ?
        {
            ob = m->goGet(temp);
            if(ob == 0)
            {
                qq.push(temp); // last primitive ?
                break;
            }
            else
            {
                temp = ob->stringify();
            }
        }
        else
        {
            zap = temp.substr(0,pos);
            temp = temp.substr(pos+1,temp.size()-1);
            ob = m->goGet(zap);
            if(ob == 0)
            {
                qq.push(zap); // primitive ?
            }
            else
            {
                zap = ob->stringify();
                temp = zap + "." + temp;
            }
        }
    }

    left = "";
    while(!qq.empty())
    {
        left = left + qq.front() + ".";
        qq.pop();
    }
    left.pop_back();
    s = left + ":" + right;

    return s;
}
//--------------------------------------------------------------------------------

// rewrite (f.g):x -> f:(g:x)
std::string Interpreter::par_dot(std::string& s)
{
    std::size_t pos = s.find_last_of('.');
    if(pos != std::string::npos && pos < s.size())
    {
        std::string temp = s.substr(0,pos); // all string until '.'
        temp += ":(";
        temp += s.substr(pos+1, s.size()-1);
        temp += ")";
        s = temp;
        par_dot(s);
    }
    return s;
}
//--------------------------------------------------------------------------------

void Interpreter::par_colon(std::string& s, std::list<std::string>& lst)
{
    std::size_t pos = s.find(":"); // position of first :
    if( pos != std::string::npos && pos < s.size() )
    {
        std::string left = s.substr(0, pos);
        left = trimSpace(left); // REMOVE LEAD/TAIL WHITESPACE
        lst.push_back(left);
        lst.push_back(":");
        s = s.substr(pos+1);
        lst.push_back(s);
    }
    else
    {
        s = trimSpace(s); // REMOVE LEAD/TAIL WHITESPACE
        lst.push_back(s);
    }
}
//--------------------------------------------------------------------------------

std::list<Object*> Interpreter::toklist(std::list<std::string> lst, Memory* m)
{
    Object* ob = 0;
    std::list<Object*> oblist;

    for(std::list<std::string>::iterator it = lst.begin(); it != lst.end(); it++)
    {
        if( (*it).empty() || *it == "" ) // error check
        {
            std::cout << "ERROR: null string for build object" << std::endl;
            throw std::runtime_error("parse() : null string for build object"); // return 0;
        }

        if(*it == ":") // make colon object
        {
            ob = new Colon(*it);
            oblist.push_back(ob);
            ob = 0;
            continue;
        }

        ob = m->goGet(*it); // look for variable||function object in memory hashes
        if(ob != 0) // mem var
        {
            oblist.push_back(ob);
            ob = 0;
            continue;
        }
        else // make new object
        {
            std::string val = *it;
            if( val.at(0) == '(' && val.at(val.size()-1) == ')' ) // block
            {
                // remove ()
                val = val.substr(1, (val.size() - 1)); // gone (
                val = val.substr(0, (val.size() - 1)); // gone )
                ob  = new Block(val);
                oblist.push_back(ob);
                ob = 0;
                continue;
            }
            else if( isdigit(val.at(0)) || ( (val.size() >= 2)&&( (val.at(0) == '-')&&isdigit(val.at(1)) ) ) ) // element
            {
                ob = new Element(atoi(val.c_str()));
                oblist.push_back(ob);
                ob = 0;
            }
            else if(val.at(0) == '<' && val.at(val.size() - 1) == '>' ) // sequence
            {
                std::list<int> ilst;

                // remove <>
                val = val.substr(1, (val.size() - 1)); // gone <
                val = val.substr(0, (val.size() - 1)); // gone >
                val = trimSpace(val);

                // add empty list HERE
                if(val.empty())
                {
                    ob = new Sequence(ilst);
                    oblist.push_back(ob);
                    ob = 0;
                    continue;
                }

                // remove bad junk before segfault
                while( !isalnum(val.at(0)) && val.size() >= 1 )
                {
                    if(val.size() == 1){val = ""; break;}
                    if(val.at(0) == '-') {break;} // a negative number
                    val = val.substr(1, (val.size() - 1));
                }

                // add empty list HERE
                if(val.empty())
                {
                    ob = new Sequence(ilst);
                    oblist.push_back(ob);
                    ob = 0;
                    continue;
                }

                // extract && store the elements of the sequence
                char* copy = (char*)(val.c_str());  // copy to give strtok for parse
                char* arr = strtok(copy, ",");      // temp array

                // get the 1st element
                Object* tmpobj = m->goGet(std::string(arr)); // have to see if list has vars: <1,2,x,3>
                if(tmpobj != 0 && tmpobj->type() == "Element")
                {
                    ilst.push_back( (static_cast<Element*>(tmpobj)->getElement() ) );
                }
                else
                {
                    ilst.push_back( atoi( arr ) );
                }

                // get the rest of the elements
                for(unsigned i = 1; arr != 0; i++)
                {
                    arr = strtok(NULL, ",");
                    if(arr)
                    {
                        tmpobj = m->goGet( std::string(arr) ); // have to see if list has vars: <1,2,x,3>
                        if(tmpobj != 0 && tmpobj->type() == "Element")
                        {
                            ilst.push_back( (static_cast<Element*>(tmpobj)->getElement() ) );
                        }
                        else
                        {
                            ilst.push_back( atoi( arr ) );
                        }
                    }
                }

                ob = new Sequence(ilst);    // list with data HERE
                oblist.push_back(ob);
                ob = 0;
            }
            else // function
            {
                ob = new Function(val);
                oblist.push_back(ob);
                ob = 0;
            }
            // end make object

        } // end if

    } // end for

  ob = 0;    // pointer clean
  delete ob;

  return oblist;
}
//--------------------------------------------------------------------------------

// convert from infix to postfix
std::list<Object*> Interpreter::postfix(std::list<Object*> lst)
{
    std::stack<Object*> s;
    std::list<Object*> pfix;
    std::list<Object*>::iterator it = lst.begin();

    while(it != lst.end())
    {
        if((*it)->type() == "Function"|| (*it)->type() == "Sequence" || (*it)->type() == "Element" || (*it)->type() == "Block")
        {
            pfix.push_back(*it);
        }
        else
        {
            if(s.empty())
            {
                s.push(*it);
            }
            else
            {
                while(!s.empty())
                {
                    pfix.push_back(s.top());
                    s.pop();
                }
                s.push(*it);
            }
        }
        it++;
    }

    while(!s.empty())
    {
        pfix.push_back(s.top());
        s.pop();
    }

    return pfix;
}
//--------------------------------------------------------------------------------

// build the AST recursively
Node* Interpreter::buildtree(std::list<Object*> lst, Memory* m)
{
    std::stack<Node*> s;
    Node* n; // center
    Node* r; // right
    Node* l; // left

    for(std::list<Object*>::iterator i = lst.begin(); i != lst.end(); i++)
    {
        if((*i)->type() == "Block") // recursive parse***
        {
            std::string xstr = (*i)->get()->stringify();
            n = parse(xstr, m);
            s.push(n);
        }
        else if( (*i)->type() == "Function"|| (*i)->type() == "Sequence" || (*i)->type() == "Element" )
        {
            n = new Node((*i)->get());
            s.push(n);
        }
        else // Colon
        {
            if(!s.empty()) // empty == do nothing
            {
                n = new Node((*i)->get());
                if(s.size() >= 2)
                {
                    r = s.top();
                    s.pop();
                    n->setRight(r);
                    r->setParent(n);
                    //
                    l = s.top();
                    s.pop();
                    n->setLeft(l);
                    l->setParent(n);
                    //
                    s.push(n);
                }
            }
        }
    }
    n = s.top();
    s.pop();

    return n;
}
//--------------------------------------------------------------------------------

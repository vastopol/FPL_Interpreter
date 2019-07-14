// utility functions used in different parts

#include "../header/func.h" // need the maps for the classifier
#include "../header/object.h" // need the maps for the classifier
#include "../header/memory.h" // need the maps for the classifier

#include <cstring> // strtok
#include <cstdlib> // atoi

//----------------------------------------------------------------------------------------------

std::string trimSpace(std::string s)     // removes any (leading || trailing) whitespace characters
{
    if(s.empty()){return s;}
    while(s.at(0) == ' ' || s.at(0) == '\t')                // remove any leading whitespace
    {
        if(s.size() == 1){return "";}
        s = s.substr(1, (s.size()-1));
    }
    while(s.at(s.size()-1) == ' ' || s.at(s.size()-1) == '\t')       // remove any trailing whitespace
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

int func_classifier(std::string s) // what type of function
{
    int ftype = -1;

    if(U_E_R_E.find(s) != U_E_R_E.end()) // int  -> int
        ftype = 0;
    if(U_E_R_S.find(s) != U_E_R_S.end()) // int  -> list
        ftype = 1;
    if(U_S_R_E.find(s) != U_S_R_E.end()) // list -> int
        ftype = 2;
    if(U_S_R_S.find(s) != U_S_R_S.end()) // list -> list
        ftype = 3;

    return ftype;
}

//----------------------------------------------------------------------------------------------

Sequence* seq_par(std::string val, Memory* m) // based on interpreter code need to parse in concat operator in action
{
    // std::cout << "sequence part: " << val << std::endl;

    Sequence* ob = 0;

    std::list<int> ilst;

    // remove <>
    val = val.substr(1, (val.size() - 1)); // gone <
    val = val.substr(0, (val.size() - 1)); // gone >

    val = trimSpace(val);

    // add empty list HERE
    if(val.empty())
    {
        ob = new Sequence(ilst);
        return ob;
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
        return ob;
    }

    // extract && store the elements of the sequence
    char* copy = (char*)(val.c_str());  // copy to give strtok for parse
    char* arr = strtok(copy, ",");      // temp array

    // 1st element
    Object* tmpobj = m->goGet(std::string(arr)); // have to see if list has vars: <1,2,x,3>
    if(tmpobj != 0 && tmpobj->type() == "Element")
    {
        ilst.push_back( (static_cast<Element*>(tmpobj)->getElement() ) );
    }
    else
    {
        ilst.push_back( atoi( arr ) );
    }

    // rest of the elements
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
    return ob;
}


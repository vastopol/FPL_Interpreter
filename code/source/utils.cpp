// utility functions used in different parts

#include "../header/func.h" // need the maps for the classifier

std::string trimSpace(std::string s)     // removes any (leading || trailing) whitespace characters
{
    if(s.empty()){return s;}
    while(s.at(0) == ' ')                // remove any leading spaces
    {
        if(s.size() == 1){return "";}
        s = s.substr(1, (s.size()-1));
    }
    while(s.at(s.size()-1) == ' ')       // remove any trailing spaces
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


#include "../header/memory.h"

/*
    private:
    // maps for holding variables
    std::map<std::string, int> elements;
    std::map<std::string, std::list<int> > sequences;
*/

//----------------------------------------------------------

Memory::~Memory()
{
    std::cout << "MEMORY DESTRUCTOR" << std::endl;
}
//---------------------------------------------------------


// MEMORY MANAGEMENT OPERATIONS

void Memory::add_element(std::string s, int i)
{
    if(!s.empty())
    {
        elements[s] = i;
    }
}
//---------------------------------------------------------

void Memory::add_sequence(std::string s, std::list<int> l)
{
    if(!s.empty())
    {
        sequences[s] = l;
    }
}
//---------------------------------------------------------

void Memory::remove_element(std::string s)
{
    std::map<std::string, int>::iterator it = elements.find(s);
    if (it != elements.end())
    {
        elements.erase(it);
    }
}
//---------------------------------------------------------

void Memory::remove_sequence(std::string s)
{
    std::map<std::string, std::list<int> >::iterator it = sequences.find(s);
    if (it != sequences.end())
    {
        sequences.erase(it);
    }
}
//---------------------------------------------------------

void Memory::print_elements()
{
    // print content (begin to end)
    for(std::map<std::string,int>::iterator it = this->elements.begin(); it != this->elements.end(); it++)
    {
        std::cout << it->first << " = " << it->second << std::endl;
    }
}
//---------------------------------------------------------

void Memory::print_sequences()
{
    // cycle container
    for(std::map<std::string, std::list<int> >::iterator it = this->sequences.begin(); it != this->sequences.end(); it++)
    {
        std::list<int>::iterator jt = it->second.begin();
        
        if(jt == it->second.end()) // empty list
        {std::cout << it->first << " = {}\n"; continue;}
        
        std::cout << it->first << " = {";
        for(; jt != --it->second.end(); jt++ ) // print list elements before last
        {
            std::cout << *jt << ",";
        }
        std::cout << *jt << "}" << std::endl; // print last
    }
}
//---------------------------------------------------------

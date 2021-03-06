#include "../header/memory.h"

Memory::~Memory()
{
    clear();
    empty_buf();
}
//----------------------------------------

// ADD
//--------------------------------------------------------------------------------
void Memory::add_element(std::string s, Element i)
{
    if(!s.empty())
    {
        elements[s] = i;
    }
}
//----------------------------------------

void Memory::add_sequence(std::string s, Sequence l)
{
    if(!s.empty())
    {
        sequences[s] = l;
    }
}
//----------------------------------------

void Memory::add_macro(std::string a, Function b)
{
    if(!a.empty())
    {
        macros[a] = b;
    }
}
//-----------------------------------------

void Memory::add_str_buf(std::string s) // queue 1 string to buffer
{
    if(!s.empty())
    {
        buffer.push_back(s);
    }
}
//-----------------------------------------

void Memory::add_str_hist(std::string s)
{
    if(!s.empty())
    {
        history.push_back(s);
    }
}
//--------------------------------------------------------------------------------

// REMOVE
//--------------------------------------------------------------------------------
void Memory::remove_element(std::string s)
{
    std::map<std::string, Element>::iterator it = elements.find(s);
    if (it != elements.end())
    {
        elements.erase(it);
    }
}
//----------------------------------------

void Memory::remove_sequence(std::string s)
{
    std::map<std::string, Sequence >::iterator it = sequences.find(s);
    if (it != sequences.end())
    {
        sequences.erase(it);
    }
}
//----------------------------------------

void Memory::remove_macro(std::string s)
{
    std::map<std::string, Function>::iterator it = macros.find(s);
    if (it != macros.end())
    {
        macros.erase(it);
    }
}
//-----------------------------------------

void Memory::empty_buf()
{
    buffer.clear();
}
//-----------------------------------------

void Memory::clear()
{
    this->elements.clear();
    this->sequences.clear();
    this->macros.clear();
}
//--------------------------------------------------------------------------------

// ACCESS
//--------------------------------------------------------------------------------
std::map<std::string, Element>& Memory::get_elements()
{
    return elements;
}
//---------------------------------------------

std::map< std::string, Sequence >& Memory::get_sequences()
{
    return sequences;
}
//---------------------------------------------

std::map<std::string, Function >& Memory::get_macros()
{
    return macros;
}
//---------------------------------------------

std::list<std::string>& Memory::get_buffer()
{
    return buffer;
}
//---------------------------------------------

Object* Memory::goGet(std::string s)
{
    std::map<std::string, Element>::iterator et = elements.find(s);
    std::map<std::string, Sequence>::iterator st = sequences.find(s);
    std::map<std::string, Function>::iterator ft = macros.find(s);
    Object* op = 0;

    if(et != elements.end())
    {
        op = &et->second;
    }
    else if(st != sequences.end())
    {
        op = &st->second;
    }
    else if(ft != macros.end())
    {
        op = &ft->second;
    }

    return op;
}

//--------------------------------------------------------------------------------

// PRINT
//--------------------------------------------------------------------------------
void Memory::print_elements()
{
    std::map<std::string, Element>::iterator it = this->elements.begin();
    for(; it != this->elements.end(); it++)
    {
        std::cout << it->first << " = ";
        it->second.print();
        std::cout << std::endl;
    }
}
//----------------------------------------

void Memory::print_sequences()
{
    std::map< std::string, Sequence>::iterator it = this->sequences.begin();
    for(; it != this->sequences.end(); it++)
    {
        std::cout << it->first << " = ";
        it->second.print();
        std::cout << std::endl;
    }
}
//--------------------------------------------------------

void Memory::print_macros()
{
    std::map<std::string, Function>::iterator it = this->macros.begin();
    for(; it != this->macros.end(); it++)
    {
        std::cout << it->first << " = ";
        it->second.print();
        std::cout << std::endl;
    }
}
//-----------------------------------------

void Memory::print_buf_status()
{
    if(buffer.empty())
    {
        std::cout << "EMPTY" << std::endl;
        return;
    }
    std::cout << "LOADED" << std::endl;
}
//-----------------------------------------

void Memory::print_buffer()
{
    if(buffer.empty())
    {
        std::cout << "EMPTY" << std::endl;
        return;
    }

    std::list<std::string>::iterator it = this->buffer.begin();
    for(; it != this->buffer.end(); it++)
    {
        std::cout << *it << std::endl;
    }
}
//-----------------------------------------

void Memory::print_history()
{
    if(history.empty())
    {
        std::cout << "EMPTY" << std::endl;
        return;
    }

    int i = 1;
    std::list<std::string>::iterator it = this->history.begin();
    for(; it != this->history.end(); it++)
    {
        std::cout << i << ":\t" << *it << std::endl;
        i++;
    }
}
//--------------------------------------------------------------------------------


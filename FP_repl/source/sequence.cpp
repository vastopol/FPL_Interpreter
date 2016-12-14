#include "../header/sequence.h"

Sequence::Sequence()
{}
//---------------------------

Sequence::Sequence(std::list<int> lst)
    : value(lst)
{}
//---------------------------

Sequence::~Sequence()
{
    // not done
}
//---------------------------

std::list<int> Sequence::getList()
{
    return value;
}
//---------------------------

std::list<int> Sequence::head()
{  
    if(value.size() <= 1)
    { 
        return value;
    }
    
    std::list<int> lst;
    lst.push_back( value.front() );
    return lst;
    
}
//---------------------------

std::list<int> Sequence::tail()
{
    if(value.size() <= 1)
    { 
        return value;
    }
    
    std::list<int> lst(value.begin()++, value.end());
    return lst;
}
//---------------------------

std::list<int> Sequence::reversal()
{
    if(value.size() <= 1)
    { 
        return value;
    }
    
    std::list<int> lst = value;
    lst.reverse();
    return lst;
}
//---------------------------

std::list<int> Sequence::rotr()
{
    if(value.size() <= 1)
    { 
        return value;
    }
    
    std::list<int> lst(value.begin()++, value.end());
    lst.push_back(value.front());
    return lst;
    
}
//---------------------------

std::list<int> Sequence::rotl()
{
    if(value.size() <= 1)
    { 
        return value;
    }
    
    std::list<int> lst(value.begin(), value.end()--);
    lst.push_front(value.back());
    return lst;
}
//---------------------------

std::list<int> Sequence::max()
{
    if(value.size() <= 1)
    { 
        return value;
    }
    
    std::list<int> lst;
    int chk = value.front(); // max
    for(std::list<int>::iterator jt = value.begin(); jt != value.end(); jt++)
    {        
        if(*jt > chk)
        {
            chk = *jt;
        }
    }
    lst.push_back(chk);
    return lst;
}
//---------------------------

std::list<int> Sequence::min()
{
    if(value.size() <= 1)
    { 
        return value;
    }
    
    std::list<int> lst;
    int chk = value.front(); // min 
    for(std::list<int>::iterator it = value.begin(); it != value.end(); it++)
    {
        if(*it < chk)
        {
            chk = *it;
        }
    }
    lst.push_back(chk);
    return lst;
}
//---------------------------

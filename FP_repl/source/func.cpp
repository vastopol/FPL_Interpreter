#include "../header/func.h"


std::list<int> head()
{  
    if(seq.size() <= 1)
    { 
        return seq;
    }
    
    std::list<int> lst;
    lst.push_back( seq.front() );
    return lst;
}
//---------------------------

std::list<int> tail()
{
    if(seq.size() <= 1)
    { 
        return seq;
    }
    
    std::list<int> lst(seq.begin()++, seq.end());
    return lst;
}
//---------------------------

std::list<int> rotr()
{
    if(seq.size() <= 1)
    { 
        return seq;
    }
    
    std::list<int> lst(seq.begin()++, seq.end());
    lst.push_back(seq.front());
    return lst;   
}
//---------------------------

std::list<int> rotl()
{
    if(seq.size() <= 1)
    { 
        return seq;
    }
    
    std::list<int> lst(seq.begin(), seq.end()--);
    lst.push_front(seq.back());
    return lst;
}
//---------------------------

std::list<int> rev()
{
    if(seq.size() <= 1)
    { 
        return seq;
    }
    
    std::list<int> lst = seq;
    lst.reverse();
    return lst;
}
//---------------------------

std::list<int> max()
{
    if(seq.size() <= 1)
    { 
        return seq;
    }
    
    std::list<int> lst;
    int chk = seq.front(); // max
    for(std::list<int>::iterator jt = seq.begin(); jt != seq.end(); jt++)
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

std::list<int> min()
{
    if(seq.size() <= 1)
    { 
        return seq;
    }
    
    std::list<int> lst;
    int chk = seq.front(); // min 
    for(std::list<int>::iterator it = seq.begin(); it != seq.end(); it++)
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
#include "../header/func.h"


std::map<std::string, int> U_E
{
    {"NEG",0},
    {"ABS",1},
    {"INC",2},
    {"DEC",3},
};

std::map<std::string, int> U_S
{
    {"HEAD",0},
    {"TAIL",1},
    {"ROTL",2},
    {"ROTR",3},
    {"REV",4}
};

//===============================================================

// fill jump tables
int (*Unary_E[])(int) // unary element
{
    neg,
    abs,
    inc,
    dec
    /* ... */
};

std::list<int> (*Unary_S[])(std::list<int>) // unary sequence
{
    head,
    tail,
    rotr,
    rotl,
    rev
    /* ... */
};


//===============================================================

int neg(int x) // x = -x
{
    return (-1) * x;
}
//---------------------------

int abs(int x) // x = |x|
{
    if(x < 0)
    {
        return (-1) * x;
    }
    else
    {
        return x;
    }
}
//---------------------------

int inc(int x) // x = x--
{
    return ++x;
}
//---------------------------

int dec(int x) // x = x++
{
    return --x;
}
//---------------------------

//===============================================================
//===============================================================

std::list<int> head(std::list<int> seq)
{  
    if(seq.size() == 1 || seq.empty())
    { 
        return seq;
    }
    
    std::list<int> lst;
    lst.push_back( seq.front() );
    return lst;
}
//---------------------------

std::list<int> tail(std::list<int> seq)
{
    if(seq.size() <= 1)
    { 
        return seq;
    }
    
    std::list<int> lst(seq.begin()++, seq.end());
    lst.pop_front();
    return lst;
}
//---------------------------

std::list<int> rotl(std::list<int> seq)
{
    if(seq.size() <= 1)
    { 
        return seq;
    }
    
    std::list<int> lst(seq.begin()++, seq.end()--);
    lst.push_front(seq.back());
    lst.pop_back();
    return lst;
}
//---------------------------

std::list<int> rotr(std::list<int> seq)
{
    if(seq.size() <= 1)
    { 
        return seq;
    }
    
    std::list<int> lst(seq.begin()++, seq.end()--);
    lst.push_back(seq.front());
    lst.pop_front();
    return lst;   
}
//---------------------------


std::list<int> rev(std::list<int> seq)
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


#include "../header/func.h"


std::map<std::string, int> U_E
{
    {"NEG",0},
    {"ABS",1},
    {"INC",2},
    {"DEC",3}
};

std::map<std::string, int> U_S_R_E
{
    {"SIZE",0},
    {"HEAD",1},
    {"LMAX",2},
    {"LMIN",3}
};

std::map<std::string, int> U_S_R_S
{
    {"TAIL",0},
    {"ROTL",1},
    {"ROTR",2},
    {"POPL",3},
    {"POPR",4},
    {"REV",5},
    {"SORT",6},
    // {"RMDUP",7}
};

//===============================================================

// fill jump tables
int (*Unary_E[])(int) // unary element return element
{
    neg,
    abs,
    inc,
    dec
    /* ... */
};

int (*Unary_S_R_E[])(std::list<int>) // unary sequence returns element
{
    size,
    head,
    lmax,
    lmin
    /* ... */
};

std::list<int> (*Unary_S_R_S[])(std::list<int>) // unary sequence returns sequence
{
    tail,
    rotr,
    rotl,
    popl,
    popr,
    rev,
    sort,
    // rmdup
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

int size(std::list<int> l)
{
    return l.size();
}
//---------------------------

int head(std::list<int> seq)
{  
    if(seq.empty())
    {
        return 0;
    }

    return seq.front();
}
//---------------------------

int lmax(std::list<int> seq)
{
    if(seq.empty())
    {
        return 0;
    }
    else if(seq.size() == 1)
    { 
        return seq.front();
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
    return chk;
}
//---------------------------

int lmin(std::list<int> seq)
{
    if(seq.empty())
    {
        return 0;
    }
    else if(seq.size() == 1)
    { 
        return seq.front();
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
    return chk;
}
//---------------------------


//===============================================================
//===============================================================



std::list<int> tail(std::list<int> seq)
{
    if(seq.size() <= 1)
    { 
        seq.clear();
        return seq;
    }

    seq.pop_front();
    return seq;
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

std::list<int> popl(std::list<int> seq)
{
    if(seq.size() <= 1)
    { 
        seq.clear();
        return seq;
    }

    seq.pop_front();
    return seq;
}
//---------------------------

std::list<int> popr(std::list<int> seq)
{
    if(seq.size() <= 1)
    { 
        seq.clear();
        return seq;
    }

    seq.pop_back();
    return seq;
}
//---------------------------

std::list<int> rev(std::list<int> seq)
{
    if(seq.size() <= 1)
    { 
        return seq;
    }

    seq.reverse();
    return seq;
}
//---------------------------

std::list<int> sort(std::list<int> seq)
{
    if(seq.size() <= 1)
    { 
        return seq;
    }

    seq.sort();
    return seq;
}
//---------------------------

/*
std::list<int> rmdup(std::list<int> seq)
{
    return seq;
}
//---------------------------
*/
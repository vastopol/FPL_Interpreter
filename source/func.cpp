#include "../header/func.h"

//===============================================================
// Map names to position in jump tables
//===============================================================

std::map<std::string, int> U_E
{
    {"neg",F_NEG},
    {"abs",F_ABS},
    {"inc",F_INC},
    {"dec",F_DEC},
    {"square",F_SQUARE},
    {"cube",F_CUBE},
    {"sqrt",F_SQRT}
};

std::map<std::string, int> U_S_R_E
{
    {"size",F_SIZE},
    {"head",F_HEAD},
    {"lmax",F_LMAX},
    {"lmin",F_LMIN},
    {"sum",F_SUM},
    {"prod",F_PROD}
};

std::map<std::string, int> U_S_R_S
{
    {"tail",F_TAIL},
    {"rotl",F_ROTL},
    {"rotr",F_ROTR},
    {"popl",F_POPL},
    {"popr",F_POPR},
    {"rev",F_REV},
    {"sort",F_SORT},
    {"rmdup",F_RMDUP}
};

//===============================================================
// fill jump tables
//===============================================================

int (*Unary_E[])(int) // unary element return element
{
    &neg,
    &abs,
    &inc,
    &dec,
    &square,
    &cube,
    &sqroot
    /* ... */
};

int (*Unary_S_R_E[])(std::list<int>) // unary sequence returns element
{
    &size,
    &head,
    &lmax,
    &lmin,
    &sum,
    &prod
    /* ... */
};

std::list<int> (*Unary_S_R_S[])(std::list<int>) // unary sequence returns sequence
{
    &tail,
    &rotr,
    &rotl,
    &popl,
    &popr,
    &rev,
    &sort,
    &rmdup
    /* ... */
};

//===============================================================
// Unary Element Returns Element
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

int square(int x) // x = x*x
{
    return x*x;
}
//---------------------------

int cube(int x) // x = x*x*x
{
    return x*x*x;
}
//---------------------------

int sqroot(int x) // x = sqrt(x)
{
    double d = x;
    d = sqrt(d);
    return (int)d;
}
//---------------------------

//===============================================================
// Unary Sequence Returns Element
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

int sum(std::list<int> seq)
{
    if(seq.empty())
    {
        return 0;
    }
    else if(seq.size() == 1)
    {
        return seq.front();
    }

    int sum = 0;
    for(std::list<int>::iterator it = seq.begin(); it != seq.end(); it++)
    {
        sum += *it;
    }
    return sum;
}
//---------------------------

int prod(std::list<int> seq)
{
  if(seq.empty())
  {
      return 0;
  }
  else if(seq.size() == 1)
  {
      return seq.front();
  }

  int prod = 1;
  for(std::list<int>::iterator it = seq.begin(); it != seq.end(); it++)
  {
      prod *= *it;
  }
  return prod;
}
//---------------------------


//===============================================================
// Unary Sequence Returns Sequence
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

std::list<int> rmdup(std::list<int> seq)
{
    if(seq.size() <= 1)
    {
        return seq;
    }

    std::list<int> lst;
    std::list<int>::iterator i = seq.begin();

    while( i != seq.end() )
    {
        if( find(lst.begin(), lst.end(), *i) != lst.end() )
        {
            i = seq.erase(i);
        }
        else
        {
            lst.push_back(*i);
            i++;
        }
    }

    return lst;
}
//---------------------------

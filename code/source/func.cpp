#include "../header/func.h"

//===============================================================
// Map names to position in jump tables
//===============================================================

std::map<std::string, int> U_E_R_E
{
    {"neg",F_NEG},
    {"abs",F_ABS},
    {"inc",F_INC},
    {"dec",F_DEC},
    {"square",F_SQUARE},
    {"cube",F_CUBE},
    {"sqrt",F_SQRT},
    {"not",F_NOT},
    {"odd",F_ODD},
    {"even",F_EVEN},
    {"zero",F_ZERO},
    {"~1",F_C_ONE},
    {"~0",F_C_ZERO},
    {"log",F_LOG}
};

std::map<std::string, int> U_E_R_S
{
    {"intsto",F_INTSTO},
    {"ones",F_ONES},
    {"zeros",F_ZEROS},
    {"list",F_LIST}
};

std::map<std::string, int> U_S_R_E
{
    {"size",F_SIZE},
    {"head",F_HEAD},
    {"max",F_MAX},
    {"min",F_MIN},
    {"sum",F_SUM},
    {"prod",F_PROD},
    {"nil",F_NIL},
    {"eq",F_EQ},
    {"neq",F_NEQ},
    {"gt",F_GT},
    {"lt",F_LT},
    {"gte",F_GTE},
    {"lte",F_LTE},
    {"gcd",F_GCD}
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
    {"rmdup",F_RMDUP},
    {"+",F_ADD},
    {"-",F_SUB},
    {"*",F_MUL},
    {"/",F_DIV},
    {"%",F_MOD},
    {"^",F_POW}
};

//===============================================================
// fill jump tables
//===============================================================

int (*Unary_E_R_E[])(int) // unary element return element
{
    &neg,
    &_abs,
    &inc,
    &dec,
    &square,
    &cube,
    &sqroot,
    &_not,
    &odd,
    &even,
    &zero,
    &c_one,
    &c_zero,
    &_log
};

std::list<int> (*Unary_E_R_S[])(int) // unary element return sequence
{
    &intsto,
    &ones,
    &zeros,
    &list
};

int (*Unary_S_R_E[])(std::list<int>) // unary sequence returns element
{
    &size,
    &head,
    &max,
    &min,
    &sum,
    &prod,
    &nil,
    &eq,
    &neq,
    &gt,
    &lt,
    &gte,
    &lte,
    &gcd
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
    &rmdup,
    &add,
    &sub,
    &mul,
    &div,
    &mod,
    &pow
};

//===============================================================
// Unary Element Returns Element
//===============================================================

int neg(int x) // x = -x
{
    return (-1) * x;
}
//---------------------------

int _abs(int x) // x = |x|
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
    return (int) sqrt(x);
}
//---------------------------

int _not(int x) // needs underscore in name or will not compile
{
    if(x == 0)
    {
        return 1;
    }
    return 0;
}
//---------------------------

int odd(int x)
{
    if(x % 2 != 0)
    {
        return 1;
    }
    return 0;
}
//---------------------------

int even(int x)
{
    if(x % 2 == 0)
    {
        return 1;
    }
    return 0;
}
//---------------------------

int zero(int x)
{
    if(x == 0)
    {
        return 1;
    }
    return 0;
}
//---------------------------

int c_one(int x)
{
    return 1;
}
//---------------------------

int c_zero(int x)
{
    return 0;
}
//---------------------------

int _log(int x)
{
    return (int) log10(x);
}
//---------------------------

//===============================================================
// Unary Element Returns Sequence
//===============================================================

std::list<int> intsto(int x)
{
    std::list<int> l;

    if(x <= 0)
    {
      return l;
    }

    for(int i = 1; i <= x; i++)
    {
        l.push_back(i);
    }

    return l;
}
//---------------------------

std::list<int> ones(int x)
{
    std::list<int> l;

    if(x <= 0)
    {
      return l;
    }

    for(int i = 1; i <= x; i++)
    {
        l.push_back(1);
    }

    return l;
}
//---------------------------

std::list<int> zeros(int x)
{
    std::list<int> l;

    if(x <= 0)
    {
      return l;
    }

    for(int i = 1; i <= x; i++)
    {
        l.push_back(0);
    }

    return l;
}
//---------------------------

std::list<int> list(int x)
{
    std::list<int> l;
    l.push_back(x);
    return l;
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

int max(std::list<int> seq)
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

int min(std::list<int> seq)
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

int nil(std::list<int> l)
{
    if(l.empty())
    {
        return 1;
    }
    return 0;
}
//---------------------------

int eq(std::list<int> l)
{
    if( l.empty() || l.size() < 2 )
    {
        return 0;
    }

    int a = l.front();
    l.pop_front();

    int b = l.front();
    l.pop_front();

    if(a == b)
    {
        return 1;
    }
    return 0;
}
//---------------------------

int neq(std::list<int> l)
{
    if( l.empty() || l.size() < 2 )
    {
        return 0;
    }

    int a = l.front();
    l.pop_front();

    int b = l.front();
    l.pop_front();

    if(a != b)
    {
        return 1;
    }
    return 0;
}
//---------------------------

int gt(std::list<int> l)
{
    if( l.empty() || l.size() < 2 )
    {
        return 0;
    }

    int a = l.front();
    l.pop_front();

    int b = l.front();
    l.pop_front();

    if(a > b)
    {
        return 1;
    }
    return 0;
}
//---------------------------

int lt(std::list<int> l)
{
    if( l.empty() || l.size() < 2 )
    {
        return 0;
    }

    int a = l.front();
    l.pop_front();

    int b = l.front();
    l.pop_front();

    if(a < b)
    {
        return 1;
    }
    return 0;
}
//---------------------------

int gte(std::list<int> l)
{
    if( l.empty() || l.size() < 2 )
    {
        return 0;
    }

    int a = l.front();
    l.pop_front();

    int b = l.front();
    l.pop_front();

    if(a >= b)
    {
        return 1;
    }
    return 0;
}
//---------------------------

int lte(std::list<int> l)
{
    if( l.empty() || l.size() < 2 )
    {
        return 0;
    }

    int a = l.front();
    l.pop_front();

    int b = l.front();
    l.pop_front();

    if(a <= b)
    {
        return 1;
    }
    return 0;
}
//---------------------------

int gcd(std::list<int> l)
{
    if( l.empty() || l.size() < 2 )
    {
        return 0;
    }

    int a = l.front();
    l.pop_front();

    int b = l.front();
    l.pop_front();

    int t = 0;
    while(b != 0)
    {
       t = b;
       b = a % b;
       a = t;
   }

    return a;
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

std::list<int> add(std::list<int> l)
{
    if( l.empty() || l.size() < 2 )
    {
        return l;
    }

    int a = l.front();
    l.pop_front();

    int b = l.front();
    l.pop_front();

    int c = a + b;
    l.push_front(c);

    return l;
}
//---------------------------

std::list<int> sub(std::list<int> l)
{
    if( l.empty() || l.size() < 2 )
    {
        return l;
    }

    int a = l.front();
    l.pop_front();

    int b = l.front();
    l.pop_front();

    int c = a - b;
    l.push_front(c);

    return l;
}
//---------------------------

std::list<int> mul(std::list<int> l)
{
    if( l.empty() || l.size() < 2 )
    {
        return l;
    }

    int a = l.front();
    l.pop_front();

    int b = l.front();
    l.pop_front();

    int c = a * b;
    l.push_front(c);

    return l;
}
//---------------------------

std::list<int> div(std::list<int> l)
{
    if( l.empty() || l.size() < 2 )
    {
        return l;
    }

    int a = l.front();
    l.pop_front();

    int b = l.front();
    l.pop_front();

    if(b == 0)
    {
      std::cout << "ERROR: div by 0" << std::endl;
      throw std::runtime_error("div() : division by 0 as rval");
    }

    int c = a / b;
    l.push_front(c);

    return l;
}
//---------------------------

std::list<int> mod(std::list<int> l)
{
    if( l.empty() || l.size() < 2 )
    {
        return l;
    }

    int a = l.front();
    l.pop_front();

    int b = l.front();
    l.pop_front();

    if(b == 0)
    {
      std::cout << "ERROR: mod by 0" << std::endl;
      throw std::runtime_error("mod() : modulo by 0 as rval");
    }

    int c = a % b;
    l.push_front(c);

    return l;
}
//---------------------------

std::list<int> pow(std::list<int> l)
{
    if( l.empty() || l.size() < 2 )
    {
        return l;
    }

    int a = l.front();
    l.pop_front();

    int b = l.front();
    l.pop_front();


    if(b < 0)
    {
        l.push_front(0);
    }
    else if(b == 0)
    {
        l.push_front(1);
    }
    else
    {
        int c = 1;
        for(int i = 0; i < b; i++)
        {
            c *= a;
        }
        l.push_front(c);
    }

    return l;
}
//---------------------------


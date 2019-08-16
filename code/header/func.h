#ifndef __FUNC_H__
#define __FUNC_H__

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

// define values for position in jump tables

// int -> int
#define F_NEG    0
#define F_ABS    1
#define F_INC    2
#define F_DEC    3
#define F_SQUARE 4
#define F_CUBE   5
#define F_SQRT   6
// booleans : int -> int
#define F_NOT   7
#define F_ODD   8
#define F_EVEN  9
#define F_ZERO 10

// int -> list
#define F_INTSTO 0
#define F_ONES   1
#define F_ZEROS  2
#define F_LIST   3

// list -> int
#define F_SIZE  0
#define F_HEAD  1
#define F_MAX   2
#define F_MIN   3
#define F_SUM   4
#define F_PROD  5
// booleans : list -> int
#define F_NIL   6
#define F_EQ    7
#define F_NEQ   8
#define F_GT    9
#define F_LT   10
#define F_GTE  11
#define F_LTE  12

// list -> list
#define F_TAIL   0
#define F_ROTL   1
#define F_ROTR   2
#define F_POPL   3
#define F_POPR   4
#define F_REV    5
#define F_SORT   6
#define F_RMDUP  7
#define F_ADD    8  // '+'
#define F_SUB    9  // '-'
#define F_MUL   10  // '*'
#define F_DIV   11  // '/'
#define F_MOD   12  // '%'

// mapping of function names to opcodes
// strings to integer index into table
extern std::map<std::string, int> U_E_R_E; // functions of type: int f(int)
extern std::map<std::string, int> U_E_R_S; // functions of type: list<int> f(int)
extern std::map<std::string, int> U_S_R_E; // functions of type: int f(list<int>)
extern std::map<std::string, int> U_S_R_S; // functions of type: list<int> f(list<int>)
//-------------------------------------------------------------------------------

// different jump tables by function type
extern int (*Unary_E_R_E[])(int);
extern std::list<int> (*Unary_E_R_S[])(int);
extern int (*Unary_S_R_E[])(std::list<int>);
extern std::list<int> (*Unary_S_R_S[])(std::list<int>);
//-------------------------------------------------------------------------------

// unary functions to operate on ELEMENT
// returns an ELEMENT
int neg(int x);    // x = -x
int abs(int x);    // x = |x|
int inc(int x);    // x = x--
int dec(int x);    // x = x++
int square(int x); // x = x*x
int cube(int x);   // x = x*x*x
int sqroot(int x); // x = sqrt(x)
int _not(int x);    // needs underscore in name or will not compile
int odd(int x);
int even(int x);
int zero(int x);
//-------------------------------------------------------------------------------

// unary functions to operate on ELEMENT
// returns a LIST
std::list<int> intsto(int x);
std::list<int> ones(int x);
std::list<int> zeros(int x);
std::list<int> list(int x);
//-------------------------------------------------------------------------------

// unary functions to operate on LIST
// returns an ELEMENT
int size(std::list<int> l);
int head(std::list<int> l);
int max(std::list<int> l);
int min(std::list<int> l);
int sum(std::list<int> l);
int prod(std::list<int> l);
int nil(std::list<int> l);
int eq(std::list<int> l);
int neq(std::list<int> l);
int gt(std::list<int> l);
int lt(std::list<int> l);
int gte(std::list<int> l);
int lte(std::list<int> l);
//-------------------------------------------------------------------------------

// unary functions to operate on LIST
// returns a LIST
std::list<int> tail(std::list<int> l);
std::list<int> rotl(std::list<int> l);
std::list<int> rotr(std::list<int> l);
std::list<int> rev(std::list<int> l);
std::list<int> popl(std::list<int> l);
std::list<int> popr(std::list<int> l);
std::list<int> sort(std::list<int> l);
std::list<int> rmdup(std::list<int> l);
std::list<int> add(std::list<int> l);
std::list<int> sub(std::list<int> l);
std::list<int> mul(std::list<int> l);
std::list<int> div(std::list<int> l);
std::list<int> mod(std::list<int> l);
//-------------------------------------------------------------------------------

#endif // __FUNC_H__

/*

function groups by argument type:
- Unary_E
  - return Element
  - return Sequence
- Unary_S
   - return Element
   - return Sequence

Names of function maps:
- U_E_R_E = takes element, returns an element
- U_E_R_S = takes element, returns an sequence
- U_S_R_E = takes sequence, returns element
- U_S_R_S = takes sequence, returns sequence

*/

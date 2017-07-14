#ifndef __FUNC_H__
#define __FUNC_H__

#include <list>
#include <string>
#include <map>
#include <iostream>

// mapping of function names to opcodes**********
// map strings to integer index
extern std::map<std::string, int> U_E;     // functions of type: int f(int)
extern std::map<std::string, int> U_S_R_E; // functions of type: int f(list<int>)
extern std::map<std::string, int> U_S_R_S; // functions of type: list<int> f(list<int>)

//-------------------------------------------------------------------------------

// different jump tables by function type
extern int (*Unary_E[])(int);
extern int (*Unary_S_R_E[])(std::list<int>);
extern std::list<int> (*Unary_S_R_S[])(std::list<int>);
//-------------------------------------------------------------------------------

// unary functions to operate on elements
// returns an ELEMENT
int neg(int x); // x = -x
int abs(int x); // x = |x|
int inc(int x); // x = x--
int dec(int x); // x = x++
// int sqr(int x); // x = x*x
// int cube(int x); // x = x*x*x

//-------------------------------------------------------------------------------

// unary functions to operate on lists 
// returns an ELEMENT
int size(std::list<int> l);
int head(std::list<int> l);
int lmax(std::list<int> l);
int lmin(std::list<int> l);

//-------------------------------------------------------------------------------

// unary functions to operate on lists 
// returns a LIST
std::list<int> tail(std::list<int> l);
std::list<int> rotl(std::list<int> l);
std::list<int> rotr(std::list<int> l);
std::list<int> rev(std::list<int> l);
std::list<int> popl(std::list<int> l);
std::list<int> popr(std::list<int> l);
std::list<int> sort(std::list<int> l);
// std::list<int> rmdup(std::list<int> l);

//-------------------------------------------------------------------------------


#endif // __FUNC_H__

/*

universals:
id  = identity

bools: 
elm = ? is element
seq = ? is sequence
nil = ? is empty sequence
lt  = less than
gt  = greater than
eq  = equal to
lte = less than or equal
gte = greater than or equal
neq = not equal

*/

/*

function groups ny argument type:
- Unary_E
- Unary_S
   - return Element
   - return Sequence
- Binary_E_E
- Binary_S_S
- Binary_E_S

*/

/*

U_E = takes element, returns an element
U_S_R_E = takes sequence, returns element
U_S_R_S = takes sequence, returns sequence

*/
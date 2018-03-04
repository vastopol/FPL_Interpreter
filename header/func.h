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
#define F_NEG  0
#define F_ABS  1
#define F_INC  2
#define F_DEC  3
#define F_SQUARE 4
#define F_CUBE 5
#define F_SQRT 6

// list -> int
#define F_SIZE 0
#define F_HEAD 1
#define F_LMAX 2
#define F_LMIN 3
#define F_SUM  4
#define F_PROD 5

// list -> list
#define F_TAIL  0
#define F_ROTL  1
#define F_ROTR  2
#define F_POPL  3
#define F_POPR  4
#define F_REV   5
#define F_SORT  6
#define F_RMDUP 7

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
int neg(int x);    // x = -x
int abs(int x);    // x = |x|
int inc(int x);    // x = x--
int dec(int x);    // x = x++
int square(int x); // x = x*x
int cube(int x);   // x = x*x*x
int sqroot(int x); // x = sqrt(x)
//-------------------------------------------------------------------------------

// unary functions to operate on lists
// returns an ELEMENT
int size(std::list<int> l);
int head(std::list<int> l);
int lmax(std::list<int> l);
int lmin(std::list<int> l);
int sum(std::list<int> l);
int prod(std::list<int> l);
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
std::list<int> rmdup(std::list<int> l);
//-------------------------------------------------------------------------------


#endif // __FUNC_H__

/*

Names of function maps:
- U_E = takes element, returns an element
- U_S_R_E = takes sequence, returns element
- U_S_R_S = takes sequence, returns sequence

*/

/*

function groups ny argument type:
- Unary_E
- Unary_S
   - return Element
   - return Sequence
- Binary_E_E (not implemented yet)
- Binary_E_S (not implemented yet)
- Binary_S_S (not implemented yet)



*/

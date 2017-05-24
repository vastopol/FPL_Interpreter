#ifndef __FUNC_H__
#define __FUNC_H__

#include <list>
#include <string>
#include <map>

// mapping of function names to opcodes**********
// map strings to int
extern std::map<std::string, int> U_E;
extern std::map<std::string, int> U_S;

// different jump tables by arg type
extern int (*Unary_E[])(int);
extern std::list<int> (*Unary_S[])(std::list<int>);


// unary functions to operate on elements
int neg(int x); // x = -x
int abs(int x); // x = |x|
int inc(int x); // x = x--
int dec(int x); // x = x++

// unary functions to operate on lists 
std::list<int> head(std::list<int> l); 
std::list<int> tail(std::list<int> l);
std::list<int> rotl(std::list<int> l);
std::list<int> rotr(std::list<int> l);
std::list<int> rev(std::list<int> l);


/*
// unfinished functions
std::list<int> sort(std::list<int> l);
std::list<int> size(std::list<int> l);
std::list<int> rmdup(std::list<int> l);
std::list<int> popl(std::list<int> l);
std::list<int> popr(std::list<int> l);
*/


#endif // __FUNC_H__

/*

bools: 
id  = identity
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
function groups:
- Unary_E
- Unary_S
- Binary_E_E
- Binary_S_S
- Binary_E_S
*/
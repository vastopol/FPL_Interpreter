#ifndef __FUNC_H__
#define __FUNC_H__

#include <list>

// so far these are unary functions, each only has 1 arg

// functions to operate on elements
int neg(int); // x = -x
int abs(int); // x = |x|
int inc(int); // x = x--
int dec(int); // x = x++

// functions to operate on lists 
std::list<int> head(std::list<int>); 
std::list<int> tail(std::list<int>);
std::list<int> rotr(std::list<int>);
std::list<int> rotl(std::list<int>);
std::list<int> rev(std::list<int>);
std::list<int> max(std::list<int>);
std::list<int> min(std::list<int>);

std::list<int> sort(std::list<int>);
std::list<int> size(std::list<int>);
std::list<int> rmdup(std::list<int>);
std::list<int> popl(std::list<int>);
std::list<int> popr(std::list<int>);

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
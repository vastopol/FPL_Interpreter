#include "../header/object.h"

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib> 

Element::Element(int i)
    : Object(),  val(i)
{}

std::string Element::stringify()
{
	std::stringstream streamz;
	streamz << this->val;
    std::string s;
    s += streamz.str();
	return s;
}

Object* Element::get() 
{ 
	Object* ptr = this;
	return ptr;
}

//------------------------------------

Sequence::Sequence(std::list<int> l)
    : Object(),  seq(l)
{}

std::string Sequence::stringify()
{
    if(this->seq.empty())
    {
        return "<>";
    }

    std::stringstream streamz;
	std::string s = "<";
    std::list<int>::iterator it = this->seq.begin();
    for(; it != --seq.end(); it++)
    {
    	streamz << *it;
        s += streamz.str(); 
        s += ",";
    }
	streamz << *it;
    s += streamz.str();
    s += ">";	
	return s;
}

Object* Sequence::get()
 { 
	Object* ptr = this;
	return ptr;
 }

//------------------------------------

Function::Function(std::string s)
    : Object(),  func(s)
{}

std::string Function::stringify()
{
	return this->func;
}

Object* Function::get()
 { 
	Object* ptr = this;
	return ptr;
 }

//------------------------------------

Colon::Colon(std::string s)
    : Object(),  col(s)
{}

std::string Colon::stringify()
{
	return this->col;
}

Object* Colon::get()
 { 
	Object* ptr = this;
	return ptr;
 }

//------------------------------------

Block::Block(std::string s)
    : Object(),  block(s)
{}

std::string Block::stringify()
{
	return this->block;
}

Object* Block::get()
 { 
	Object* ptr = this;
	return ptr;
 }
 //------------------------------------

 
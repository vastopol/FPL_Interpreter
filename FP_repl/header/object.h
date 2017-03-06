// functions for object manipulation

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <list>
#include <string>

class Object
{
    public:
        Object();
        virtual ~Object();
        virtual std::string type() = 0;
};
//---------------------------------

class Element : public Object
{
    private:
        int val;
    
    public:
        Element();
        Element(int)
        ~Element(); 
        std::string type();
};
//---------------------------------

class Sequence : public Object
{
    private:
        std::list<int> seq
    
    public:
        Sequence();
        Sequence(std::list<int>);
        ~Sequence();
        std::string type();

        // operate on lists  // maybe these should be part of function class
        std::list<int> getList();
        std::list<int> head(); 
        std::list<int> tail();
        std::list<int> reverse();
        std::list<int> rotr();
        std::list<int> rotl();
        std::list<int> max();
        std::list<int> min();
        
};
//---------------------------------

class Function : public Object
{
    private:
        std::string fun;
    
    public:
        Function();
        Function(std::string);
        ~Function(); 
        std::string type();
};
//---------------------------------

class Colon : public Object
{
    private:
        std::string col;
    
    public:
        Colon();
        Colon(std::string);
        ~Colon();   
        std::string type();
};
//---------------------------------

class Block : public Object  // to reparse again
{
    private:
        std::string block;
    
    public:
        Block();
        Block(std::string);
        ~Block();   
        std::string type();
};
//---------------------------------

#endif // __OBJECT_H__
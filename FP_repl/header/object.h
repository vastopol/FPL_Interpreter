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
        virtual void print() = 0;
};
//---------------------------------

class Element : public Object
{
    private:
        int val;
    
    public:
        Element() {val = 0;}
        Element(int i) {val = i;}
        ~Element(); 
        std::string type() {return "Element";} 
        void print() {std::cout << this->val;}
        int getElement() {return val;}
};
//---------------------------------

class Sequence : public Object
{
    private:
        std::list<int> seq;
    
    public:
        Sequence();
        Sequence(std::list<int> l) {seq = l;}
        ~Sequence();
        std::string type() {return "Sequence";}
        void print()
        {
            if(seq.empty())
            {
                std::cout << "<>" << std::endl;
                return;
            }

            std::list<int>::iterator it = this->seq.begin();
            std::cout << "<";
            for(; it != this->seq.end()--; it++)
            {
                std::cout << *it << ",";
            }
            std::cout << *it << ">" << std::endl;
        }
        std::list<int> getList() {return seq;}

        
};
//---------------------------------

class Function : public Object
{
    private:
        std::string func;
    
    public:
        Function();
        Function(std::string s) {func = s;}
        ~Function(); 
        std::string type() {return "Function";}
        void print() {std::cout << func;}
        std::string getFunc() {return func;}
};
//---------------------------------

class Colon : public Object
{
    private:
        std::string col;
    
    public:
        Colon();
        Colon(std::string s) {col = s;}
        ~Colon();   
        std::string type() {return "Colon";}
        void print() {std::cout << col;}
        std::string getColon() {return col;}
};
//---------------------------------

class Block : public Object  // to reparse again
{
    private:
        std::string block;
    
    public:
        Block();
        Block(std::string s) {block = s;}
        ~Block();   
        std::string type() {return "Block";}
        void print() {std::cout << this->block;}
        std::string getBlock() {return this->block;}
};
//---------------------------------

#endif // __OBJECT_H__
// functions for object manipulation

#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

#include <list>

class Sequence
{
    private:
        std::list<int> value;
    
    public:
        Sequence();
        Sequence(std::list<int>);
        ~Sequence();

        // operate on lists
        std::list<int> getList();
        std::list<int> head(); 
        std::list<int> tail();
        std::list<int> reversal();
        std::list<int> rotr();
        std::list<int> rotl();
        std::list<int> max();
        std::list<int> min();
        
};
//---------------------------------


#endif // __SEQUENCE_H__
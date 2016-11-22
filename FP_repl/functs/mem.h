#ifndef __MEM_H__
#define __MEM_H__

#include <iostream>
#include <string>
#include <list>
#include <map>

class Memory
{
    public:
        // maps for holding variables
        std::map<std::string, int> elements;
        std::map<std::string, std::list<int> > sequences;
        
        // functions 
        Memory(){};
        ~Memory(){};
        
        /*
        
        // memory operations
        
        add_element(x);
        add_sequence(x);
        remove_element(x);
        remove_sequence(x);
        print_elements()
        print_sequences()
        
        */
        
};

#endif // __MEM_H__
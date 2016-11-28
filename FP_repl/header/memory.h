#ifndef __MEM_H__
#define __MEM_H__

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <iterator>

class Memory
{
    private:
        // maps for holding variables
        std::map<std::string, int> elements;
        std::map<std::string, std::list<int> > sequences;
    
    public:        
        Memory(){};
        ~Memory();
        
        void add_element(std::string, int);
        void add_sequence(std::string, std::list<int>);
        void remove_element(std::string);
        void remove_sequence(std::string);
        void print_elements();
        void print_sequences();  
};

#endif // __MEM_H__
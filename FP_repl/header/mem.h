#ifndef __MEM_H__
#define __MEM_H__

#include <iostream>
#include <string>
#include <list>
#include <map>

class Memory
{
    private:
        // maps for holding variables
        std::map<std::string, int> elements;
        std::map<std::string, std::list<int> > sequences;
    
    public:        
        // functions
        Memory(){};
        ~Memory(){};
        
        // public interface memory operations
        void add_element(int);
        void add_sequence(std::list<int>);
        void print_elements();
        void print_sequences();
        void remove_element(std::string);
        void remove_sequence(std::string);
            
};

#endif // __MEM_H__
#ifndef __MEM_H__
#define __MEM_H__

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <iterator>

#include "object.h"

class Memory
{
    private:
        // maps for holding variables
        std::map<std::string, int> elements;
        std::map<std::string, std::list<int> > sequences;
        std::map<std::string, std::string> macros;  // macros represent functions
        std::list<std::string> buffer; // list of arguments to repl to be processed in sequence
    
    public:        
        Memory(){};
        ~Memory();
        
        // ADD
        void add_element(std::string, int);
        void add_sequence(std::string, std::list<int>);
        void add_macro(std::string, std::string);
        void add_str_buf(std::string); // queue 1 string to buffer
        
        // REMOVE
        void remove_element(std::string);
        void remove_sequence(std::string);
        void remove_macro(std::string);
        void empty_buf(); // empty whole buffer
        void clear();
        
        // ACCESS
        std::map<std::string, int>& get_elements();
        std::map<std::string, std::list<int> >& get_sequences();
        std::map<std::string, std::string>& get_macros();
        std::list<std::string>& get_buffer();
        
        // PRINT
        void print_elements();
        void print_sequences(); 
        void print_macros();
        void print_buf_status(); // print if full/empty buffer
        void print_buf();        // print buffer content
};

#endif // __MEM_H__
#ifndef __MEM_H__
#define __MEM_H__

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <iterator>

#include "object.h"

class Object;
class Element;
class Sequence;
class Function;

class Memory
{
    private:
        // maps for holding variables
        std::map<std::string, Element> elements;
        std::map<std::string, Sequence > sequences;
        std::map<std::string, Function> macros;             // macros representing functions
        std::list<std::string> buffer;                      // list of arguments to be processed in sequence
        std::list<std::string> history;                     // list of commands entered - append only

    public:
        Memory() {};
       ~Memory();

        // ADD
        void add_element(std::string, Element);
        void add_sequence(std::string, Sequence);
        void add_macro(std::string, Function);
        void add_str_buf(std::string);                      // queue 1 string to buffer
        void add_str_hist(std::string);                     // write to history (logs all inputs)

        // REMOVE
        void remove_element(std::string);
        void remove_sequence(std::string);
        void remove_macro(std::string);
        void empty_buf();                                   // empty whole buffer
        void clear();

        // ACCESS
        std::map<std::string, Element>& get_elements();
        std::map<std::string, Sequence >& get_sequences();
        std::map<std::string, Function >& get_macros();
        std::list<std::string>& get_buffer();
        Object* goGet(std::string);                        // fetch the object represented by string name: Elem,Seq,Fun

        // PRINT
        void print_elements();
        void print_sequences();
        void print_macros();
        void print_buf_status();                            // print if full/empty buffer
        void print_buffer();                                // print buffer content
        void print_history();                               // print the history of commands
};

#endif // __MEM_H__
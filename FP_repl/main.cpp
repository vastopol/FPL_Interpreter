#include "header/pattern.h"
#include "header/syscom.h"
#include "header/memory.h"

#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

int main()
{
std::cout << "FP Engine" << std::endl;
std::cout << "Enter a command OR an expression/equation to evaluate" << std::endl;

std::string input;
Memory* variables = new Memory();   // pointer to memory block for variable storage

do
{
    // get user input
    std::cout << "$ ";
    getline(std::cin, input);     
    if(input.empty()){continue;}
    
    // if starts with "#" parse, generate expression tree, execute on root of tree
    if(input.at(0) == '#') 
    {
        input = input.substr(1, input.size()-1); // input now cut out "#"
        Pattern* P = new Pattern(input);         // construct pattern with
        
        // PARSE
        try
        {
            P -> setRoot( P -> getI() -> parse(input, variables) );
        }
        catch(std::exception &e)
        {
            std::cout << "ERROR: Parse" << std::endl;
            std::cout << e.what() << std::endl;
        }
        
        // EXECUTE
        try
        {
            P -> getA() -> exec( P -> getRoot() );
        }
        catch(std::exception &e)
        {
            std::cout << "ERROR: Execute" << std::endl;
            std::cout << e.what() << std::endl;
        }
    }   
    else 
    {
        com(input, variables); // call COM() for syscommands && memory interaction
    }
}
while(1);

std::cout << "END" << std::endl;

return 0;
}
//=====================================================


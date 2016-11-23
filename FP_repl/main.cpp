#include "header/interpreter.h"
#include "header/syscom.h"
#include "header/memory.h"

#include <iostream>
#include <string>
#include <cstring>

int main()
{
std::cout << "FP Engine" << std::endl;
std::cout << "Enter a command OR an expression/equation to evaluate" << std::endl;

std::string input;
Memory variables; // memory block for variable storage

do
{
    // get user input
    std::cout << ">>> ";
    getline(std::cin, input);     
    if(input.empty()){continue;}
    
    // if starts with "#"  parse && generate expression tree
    // then call to evaluate root of Equation/Expression
    if(input.substr(0, 1) == "#") 
    {
        size_t pos = 1;             // real input is past signal
        input = input.substr(pos);  // input now cut out "%"
        parse(input, variables);                // call parse()
        // eval...?
    }   
    else 
    {
        com(input, variables); // call COM() for syscommands / memory interaction
    }
}
while(1);

std::cout << "END" << std::endl;

return 0;
}
//=====================================================


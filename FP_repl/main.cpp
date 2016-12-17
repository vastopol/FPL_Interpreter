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
        // GET USER INPUT
        std::cout << "$ ";
        getline(std::cin, input);  
        
        // PROCESS INPUT
        if(!input.empty())
        {
            process(input, variables);
        }
    }
    while(1);

return 0;
}
//=====================================================

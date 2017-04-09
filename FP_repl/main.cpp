#include "header/syscom.h"
#include "header/memory.h"

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

int main()
{
    std::cout << "FP Engine" << std::endl;
    std::cout << "Enter a command OR an expression to evaluate" << std::endl;
    
    std::string input;
    Memory* storage = new Memory();   // pointer to memory block for variable storage
    
    do
    {
        std::cout << "$$ ";
        getline(std::cin, input);  

        process(input, storage);
    }
    while(1);

return 0;
}
//=====================================================

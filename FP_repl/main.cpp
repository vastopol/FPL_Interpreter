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
    std::cout << "Enter a command OR an expression/equation to evaluate" << std::endl;
    
    std::string input;
    Memory* variables = new Memory();   // pointer to memory block for variable storage
    
    do
    {
        // GET USER INPUT
        std::cout << "$$ ";
        getline(std::cin, input);  
        
        // PROCESS INPUT
        if(!input.empty())
        {
            // secret dirty hook to unix api for convenience
            if(input == "BASH_HOOK!")
            {
                system("bash"); // will fail on non *nix systems
            }
            
            process(input, variables);
        }
    }
    while(1);

return 0;
}
//=====================================================

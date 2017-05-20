#include "header/syscom.h"
#include "header/memory.h"

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

void c_line(int argc, char** argv, Memory* storage); // comline arg to run a file

//=====================================================
int main(int argc, char** argv)
{
    std::string input;
    Memory* storage = new Memory();   // pointer to memory block for variable storage
   
    c_line(argc, argv, storage); // handle any command line arguments to run a file

    std::cout << "FP Engine" << std::endl;
    std::cout << "Enter a command OR an expression to evaluate" << std::endl;
    do
    {
        std::cout << "$$ ";
        getline(std::cin, input); 

        if(input == "BASH")
        {
            system("bash"); // bad bad
        }
        else
        {
            process(input, storage);
        }
    }
    while(1);

return 0;
}
//=====================================================

void c_line(int argc, char** argv, Memory* storage) // handle comline arg to run a file
{
    if(argc >= 3)
    {
        std::cout << "comline arg num err" << std::endl;
        delete storage; // delete memory object
        storage = 0; 
        exit(0);
    }
    else if(argc == 2)
    {
        std::string ifile = std::string(argv[1]);

        load(ifile,storage);
        run(storage);

        delete storage; // delete memory object
        storage = 0; 
        exit(0);
    }
}
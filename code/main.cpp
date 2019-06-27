#include "header/syscom.h"
#include "header/memory.h"

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

void c_line(int argc, char** argv, Memory* storage); // handle comline args to run files

//=====================================================
int main(int argc, char** argv)
{
    std::string input;
    Memory* storage = new Memory();   // pointer to memory block for variable storage

    c_line(argc, argv, storage);      // handle any command line arguments to run a file

    std::cout << "FPL Interpreter" << std::endl;
    std::cout << "Version 1.2" << std::endl;

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

// handle comline args to run files
void c_line(int argc, char** argv, Memory* storage)
{
    if(argc < 2)
    {
        return;
    }

    std::string ifile;
    for(int i = 1; i < argc ; i++)
    {
        ifile = std::string(argv[i]);
        load(ifile,storage);
        run(storage);
    }

    delete storage; // delete memory object
    storage = 0;
    exit(0);
}
//------------------------------------------------------

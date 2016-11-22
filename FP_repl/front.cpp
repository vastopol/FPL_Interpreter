#include "functs/parse.h"
#include "functs/com.h"

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main()
{
std::cout << "FP Engine" << std::endl;
std::cout << "Enter a command OR an expression/equation to evaluate" << std::endl;

std::string input;

do
{
    // get user input
    std::cout << ">>> ";
    getline(cin, input);     
    if(input.empty()){continue;}
    
    // if starts with "%"  parse && generate expression tree
    // then call to evaluate root of Equation/Expression
    if(input.substr(0, 1) == "%") 
    {
        size_t pos = 1;             // real input is past signal
        input = input.substr(pos);  // input now cut out "%"
        parse(input);                // call parse()
        // eval...?
    }   
    else 
    {
        com(input); // call COM() for syscommands /  memory interaction
    }
    
}
while(1);

std::cout << "END" << std::endl;

return 0;
}
//=====================================================


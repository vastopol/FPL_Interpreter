// FP parser harness

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <list>
#include <vector>

using namespace std;

int main(){

std::string input;           // initial str to convert to int
std::string::size_type sz;   // alias of size_t

do{
    
    std::cout << ">>> ";
    std::getline(std::cin, input);
    std::cout << input << std::endl;
    int xep = atoi(input.c_str());
    std::cout << xep << std::endl; // 
    
}while(1);

return 0;
}
//=========================================================
//=========================================================



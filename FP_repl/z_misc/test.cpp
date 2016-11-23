// FP parser harness

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <list>
#include <vector>
#include <map>

int main(){

std::string input;           // initial str to convert to int
std::string::size_type sz;   // alias of size_t
std::map<std::string, int> var_map;

do{
    std::cout << ">>> ";
    std::getline(std::cin, input);
    
    if(input == "QUIT")
    {break;}
    
    std::cout << input << std::endl; // echo var name
    int value = atoi(input.c_str());  // convert to integer
    std::cout << value << std::endl; // echo num
        
    var_map[input] = value; // store the "name = value"
    
}while(1);

// print content (begin to end)
for(std::map<std::string,int>::iterator it = var_map.begin(); it != var_map.end(); it++)
{
    std::cout << it->first << " = " << it->second << std::endl;
}

return 0;
}
//=========================================================
//=========================================================



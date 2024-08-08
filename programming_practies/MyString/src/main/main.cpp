#include "../funcs/myString.hpp"


int main()
{
    try{
        myString first;
        //myString second = "Nikita Konturov";
        //first.replace(second, 7, 6);
        std::cin >> first;
        std::cout << first << "\n";
    } 
    catch(std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
 return 0;
}
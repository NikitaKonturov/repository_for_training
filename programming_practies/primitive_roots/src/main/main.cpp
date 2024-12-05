#include<chrono>
#include "../funcs/funcs.hpp"
#include "cmath"
#include "numeric"


int main()
{
    try {

    for (size_t i = 2; i < 13; ++i) {
        size_t count = 0;
        size_t temp = 0;
        for (size_t j = 1; j < 13; ++j) {
            if(((size_t)(std::pow(i, j)) % 13) == 1) {
                ++count;
                temp = j;
            }
        }
        if(count == 1 && temp == 12) {
            std::cout << i << std::endl;
        }

    }
    



    }
    catch(std::exception err) {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}


#include "../funcs/funcs.hpp"


int main()
{
    size_t gamma = 0x51;
    std::string chipherText(7, '\0');

    chipherText[0] = 0x03;
    chipherText[1] = 0x3e;
    chipherText[2] = 0x30;
    chipherText[3] = 0x3c;
    chipherText[4] = 0x38;
    chipherText[5] = 0x3f;
    chipherText[6] = 0x36;
    
    for (size_t i = 0; i < chipherText.size(); ++i) {
        chipherText[i] ^= gamma;
    }
    
    std::cout << chipherText << std::endl;



    //std::cout << "Hello world!" << std::endl;
    return 0;
}

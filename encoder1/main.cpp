#include <iostream>
#include <array>
#include "SR/SR.hpp"
#include "LSFR/LSFR.hpp"

bool funckF(std::bitset<3> input) {
    
    return input[2];
}

int main() {
    LSFR<5> lsfr({1, 2, 4}, 0b01001);
    SR<7> sr([](std::bitset<7> source){
        bool k2 = source[1];
        bool k4 = source[3];
        bool k6 = source[5];
        bool res = k2&k4 ^ k2&k6 ^ k4&k6;
        res ^= source[6];
        source = 0;
        source ^= res;
        source &= 1; 
        return source;
    },0b0111000);
    std::bitset<20> gamma = 0;
    std::bitset<20> plainText = 0b00110101001110010000;
    std::bitset<2> lDelayRegister = 0b01;
    std::bitset<2> rDelayRegister = 0b10;


    uint8_t substitution[16] = {0x4, 0x7, 0x6, 0xC, 0x0, 0x3, 0xE, 0xF, 0xA, 0xD, 0x1, 0x2, 0x9, 0xB, 0x8, 0x5};     

    uint8_t inputSubstitution = 0;
    std::bitset<3> inputFuncF = 0;
    for (size_t i = 0; i < 20; ++i) {
        std::cout << i << '\n';
        lsfr.print();
        sr.print();
        inputFuncF = 0b000;
        std::cout << lsfr[4] << lsfr[2] << lsfr[0] << '\n';
        inputFuncF ^= lsfr[4];
        inputFuncF <<= 1;
        inputFuncF ^= lsfr[2];
        inputFuncF <<= 1;
        inputFuncF ^= lsfr[0]; 
        std::wcout << "Input funnc f " << inputFuncF << '\n';
        bool outFuncF = funckF(inputFuncF);
        std::cout << "outFuncF: " << outFuncF << '\n';
        bool xorSR = sr[0] ^ sr[3] ^ sr[6];
        std::cout << "xorSR: " << xorSR << '\n';

        std::cout << "lDelayRegister: " << lDelayRegister << '\n';
        std::cout << "rDelayRegister: " << rDelayRegister << '\n';
        inputSubstitution = 0;
        inputSubstitution ^= lDelayRegister[0] & 1;
        inputSubstitution <<= 1;
        inputSubstitution ^= lDelayRegister[1] & 1;
        inputSubstitution <<= 1;
        inputSubstitution ^= rDelayRegister[1] & 1;
        inputSubstitution <<= 1;
        inputSubstitution ^= rDelayRegister[0] & 1;
        inputSubstitution &= 0x0f;
        std::cout << "inputSubstitution: " << std::bitset<4>(inputSubstitution) << '\n';
        lDelayRegister <<= 1;
        lDelayRegister ^= outFuncF & 1;
        rDelayRegister <<= 1;
        rDelayRegister ^= xorSR & 1;
        std::bitset<4> outputSubstitution = substitution[inputSubstitution];
        std::cout << "outputSubstitution: " << outputSubstitution << '\n';

        bool gammaBit = 0;

        if(outputSubstitution[1] ^ outputSubstitution[2] == 1) {
            gammaBit = xorSR | outputSubstitution[0];
        } else {
            gammaBit = outFuncF & outputSubstitution[3];
        }
        gamma ^= gammaBit;
        if(i == 19) {
            break;
        }
        gamma <<= 1;
        lsfr.shift_LSFR();
        sr.shift_SR();
    }   
    std::cout << "Gamma: " << gamma << '\n';
    std::cout << "Cipher text: " << (gamma ^ plainText) << std::endl;

    return 0;
}
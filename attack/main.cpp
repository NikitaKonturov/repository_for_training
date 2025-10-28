#include "LSFR/LSFR.hpp"
#include <sstream>

bool funcF(std::bitset<11> source1, std::bitset<5>source2) {
    return ((source1[7] & source1[3] & source1[0]) | ((source1[7] ^ 1) & (source1[3] ^ 1) & (source1[0] ^ 1))) ^ source2[3];
}

int main(){
    LSFR<11> R1({1}, 0b10100111010);
    LSFR<5> R2({1}, 0b11010);
    R2.print();
    std::stringstream ss;

    size_t size = 500;

    for (size_t i = 0; i < size; ++i) {
        ss << funcF(R1.get_bitset(), R2.get_bitset());
        R1.shift_LSFR();
        R2.shift_LSFR();
    }
    std::string gamma = ss.str();

    std::vector<std::pair<uint16_t, uint16_t>> statistics(5);
    
    std::cout << "Gamma: " << gamma << '\n';

    for (size_t i = 0; i < size; ++i) {
        if(gamma[i] == '0') {
            ++(statistics[i % 5].first);
        } else {
            ++(statistics[i % 5].second);
        }
    }
    
    std::string res(5, ' ');
    for (size_t i = 0; i < 5; ++i) {
        std::cout << i << ") 0:" << statistics[i].first << " 1: " << statistics[i].second << '\n';
        if(statistics[i].first > statistics[i].second) {
            res[(i+1) % 5] = '0';
        } else {
            res[(i+1) % 5] = '1';
        }
    }

    std::cout << "Key: " << res << std::endl;
    
    return 0;
}


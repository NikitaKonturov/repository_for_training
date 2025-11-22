#include "LSFR/LSFR.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>


void tactFunck(LSFR<19>& R1, LSFR<22>& R2, LSFR<23>& R3, std::vector<uint8_t>& tactVector){
 bool majority = ((R1.get_bit(8) & R2.get_bit(10)) | 
                    (R1.get_bit(8) & R3.get_bit(10)) | 
                    (R2.get_bit(10) & R3.get_bit(10)));
    
    // Тактируем регистры, у которых бит совпадает с мажоритарным значением
    if (R1.get_bit(8) == majority) {
        R1.shift_LSFR();
        ++tactVector[0];
    }
    if (R2.get_bit(10) == majority) {
        R2.shift_LSFR();
        ++tactVector[1];
    }
    if (R3.get_bit(10) == majority) {
        R3.shift_LSFR();
        ++tactVector[2];
    }
}

int main() {
    // (76, 76, 76, 101)
    std::pair<size_t, size_t> probability1({0, 0});
    // (79, 79, 79, 105)
    std::pair<size_t, size_t> probability2({0, 0});
    // (80, 80, 80, 105)
    std::pair<size_t, size_t> probability3({0, 0});
    // (79, 80, 81, 106)
    std::pair<size_t, size_t> probability4({0, 0});
    // (82, 82, 82, 109)
    std::pair<size_t, size_t> probability5({0, 0});

    std::set<std::vector<uint8_t>> allTacts;

    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (size_t i = 0; i < 1000000; ++i) {
        LSFR<19>R1({14, 17, 18, 19});
        LSFR<22>R2({21, 22});
        LSFR<23>R3({8, 21, 22, 23});
        std::vector<uint8_t> tactVector{0, 0, 0};
        
        uint64_t key = static_cast<uint64_t>(rand());
        uploading_the_key<19>(R1, key);
        uploading_the_key<22>(R2, key);
        uploading_the_key<23>(R3, key);
        
        uint32_t frame = static_cast<uint32_t>(rand()) & 0x7ffff;
        uploading_the_frame<19>(R1, frame);
        uploading_the_frame<22>(R2, frame);
        uploading_the_frame<23>(R3, frame);
        
        for (size_t j = 0; j < 100; ++j) {
            tactFunck(R1, R2, R3, tactVector);
        }
        tactFunck(R1, R2, R3, tactVector);      

        if(tactVector[0] == 76 && tactVector[1] == 76 && tactVector[2] == 76) {
            ++probability1.first;
        }

        allTacts.insert(tactVector);

        for (size_t j = 0; j < 4; ++j) {
            tactFunck(R1, R2, R3, tactVector); 
        }

        if(tactVector[0] == 79 && tactVector[1] == 79 && tactVector[2] == 79) {
            ++probability2.first;
        } else if(tactVector[0] == 80 && tactVector[1] == 80 && tactVector[2] == 80) {
            ++probability3.first;
        }

        allTacts.insert(tactVector);
        
        tactFunck(R1, R2, R3, tactVector); 
        
        if(tactVector[0] == 79 && tactVector[1] == 80 && tactVector[2] == 81) {
            ++probability4.first;
        }

        allTacts.insert(tactVector);

        for (size_t j = 0; j < 3; ++j) {
            tactFunck(R1, R2, R3, tactVector); 
        }

        if(tactVector[0] == 82 && tactVector[1] == 82 && tactVector[2] == 82) {
            ++probability5.first;
        }
  
        allTacts.insert(tactVector);

        std::cout << "#################(" << i << ")#################" << '\n';
        std::cout << "Probability P(76, 76, 76, 101): " << (static_cast<double>(probability1.first) / static_cast<double>(allTacts.size())) * 10000 << '\n';
        std::cout << "Probability P(79, 79, 79, 105): " << (static_cast<double>(probability2.first) / static_cast<double>(allTacts.size())) * 10000 << '\n';
        std::cout << "Probability P(80, 80, 80, 105): " << (static_cast<double>(probability3.first) / static_cast<double>(allTacts.size())) * 10000 << '\n';
        std::cout << "Probability P(79, 80, 81, 106): " << (static_cast<double>(probability4.first) / static_cast<double>(allTacts.size())) * 10000 << '\n';
        std::cout << "Probability P(82, 82, 82, 109): " << (static_cast<double>(probability5.first) / static_cast<double>(probability5.second)) * 10000 << '\n';
    
    }

    std::cout << "Probability P(76, 76, 76, 101): " << (static_cast<double>(probability1.first) / static_cast<double>(probability1.second)) * 10000 << '\n';
    std::cout << "Probability P(79, 79, 79, 105): " << (static_cast<double>(probability2.first) / static_cast<double>(probability2.second)) * 10000 << '\n';
    std::cout << "Probability P(80, 80, 80, 105): " << (static_cast<double>(probability3.first) / static_cast<double>(probability3.second)) * 10000 << '\n';
    std::cout << "Probability P(79, 80, 81, 106): " << (static_cast<double>(probability4.first) / static_cast<double>(probability4.second)) * 10000 << '\n';
    std::cout << "Probability P(82, 82, 82, 109): " << (static_cast<double>(probability5.first) / static_cast<double>(probability5.second)) * 10000 << '\n';
    

    return 0;
}


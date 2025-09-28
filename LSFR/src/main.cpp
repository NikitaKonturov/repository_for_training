#include <iostream>
#include "LSFR/LSFR.hpp"

int main(int args, char** argv) {
    LSFR<19> test({14, 17, 18, 19});

    uint32_t frame = 0;
    uint64_t key = 0;
    std::cout << "Enter the frame number in decimal: "; 
    std::cin >> frame;
    std::cout << "Enter key in decimal: ";
    std::cin >> key; 
    std::cout << '\n';

    uploading_the_key(test, key);
    uploading_the_frame(test, key);
    

    test.print();
return 0;
}
// k29 k32 k33
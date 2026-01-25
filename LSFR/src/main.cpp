#include <iostream>
#include "LSFR/LSFR.hpp"

int main(int args, char** argv) {
    LSFR<19> R1({14, 17, 18, 19});
    LSFR<22> R2({21, 22});
    LSFR<23> R3({8, 21, 22, 23});
    LSFR<17> R4({12, 17});
    

    uint32_t frame = 68425;
    uint64_t key = 243443;
   

    uploading_the_key(R1, key);
    uploading_the_frame(R1, key);
    
    uploading_the_key(R2, key);
    uploading_the_frame(R2, key);
    
    uploading_the_key(R3, key);
    uploading_the_frame(R3, key);
    
    uploading_the_key(R4, key);
    uploading_the_frame(R4, key);
    


    R1.print();
    R2.print();
    R3.print();
    R4.print();
return 0;
}
// k29 k32 k33
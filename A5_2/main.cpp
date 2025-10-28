#include"encoder/encoder.hpp"

int main() {
    std::cout << "Frame 995"  << std::endl;  
    A5_2 encoder1(0b101010011111001111111111001010101101010010001010100010011001010, 995);
    std::cout << "Check";
    std::cout << "Gamma: " << encoder1.get_gamma() << std::endl;

    encoder1.print_equations();
   
    // std::cout << "Frame 996"  << std::endl;  
    // A5_2 encoder2(0b101010011111001111111111001010101101010010001010100010011001010, 996);
    // std::cout << "Gamma: " << encoder2.get_gamma() << std::endl;

    // std::cout << "Frame 997"  << std::endl;  
    // A5_2 encoder3(0b101010011111001111111111001010101101010010001010100010011001010, 997);
    // std::cout << "Gamma: " << encoder3.get_gamma() << std::endl;

    // std::cout << "Frame 998"  << std::endl;  
    // A5_2 encoder4(0b101010011111001111111111001010101101010010001010100010011001010, 998);
    // std::cout << "Gamma: " << encoder4.get_gamma() << std::endl;

}
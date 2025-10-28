#ifndef ENCODER_HPP
#define ENCODER_HPP
#include <bitset>
#include <string>
#include <iostream>
#include <unordered_map>
#include "../LSFR/LSFR.hpp"


class A5_2 {
 private:
    size_t countOfReplaces = 0;
    LSFR<19> _R1_ = LSFR<19>({14, 17, 18, 19}, 0);
    LSFR<22> _R2_ = LSFR<22>({21, 22}, 0);
    LSFR<23> _R3_ = LSFR<23>({8, 21, 22, 23}, 0);
    LSFR<17> _R4_ = LSFR<17>({12, 17}, 0);
    std::bitset<64> _key_;
    std::bitset<22> _frame_;
    std::vector<std::map<std::string, uint8_t>> allEquations = {};
    std::unordered_map<std::string, std::string> table_of_repleces = {};
    void __initA5_2__();
    bool __tact__(bool calcEquation);
    bool __majority_function__(std::bitset<3> input);
    std::map<std::string, uint8_t> shortening_the_equation(std::map<std::string, uint8_t> equation);
    std::map<std::string, uint8_t> xor_equations(std::map<std::string, uint8_t> lVal, std::map<std::string, uint8_t> rVal);
    std::map<std::string, uint8_t> multiplay_equations(std::map<std::string, uint8_t> lVal, std::map<std::string, uint8_t> rVal);
    std::map<std::string, uint8_t> replaces_monom(std::map<std::string, uint8_t> source);
    public:
    
    A5_2(std::bitset<64> key, std::bitset<22> frame);
    A5_2(A5_2& source) = default;
    ~A5_2() = default;

    void print_equations();
    std::bitset<228> get_gamma();
    std::bitset<19> get_R1();
    std::bitset<22> get_R2();
    std::bitset<23> get_R3();
    std::bitset<17> get_R4();
};



#endif //ENCODER_HPP
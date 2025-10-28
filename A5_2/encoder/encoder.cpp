#include "encoder.hpp"

#include <string>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <algorithm>
#include <regex>


void A5_2::__initA5_2__()
{
    uploading_the_key(this->_R1_, this->_key_.to_ullong());
    uploading_the_frame(this->_R1_, this->_frame_.to_ullong());

    uploading_the_key(this->_R2_, this->_key_.to_ullong());
    uploading_the_frame(this->_R2_, this->_frame_.to_ullong()); 

    uploading_the_key(this->_R3_, this->_key_.to_ullong());
    uploading_the_frame(this->_R3_, this->_frame_.to_ullong());

    uploading_the_key(this->_R4_, this->_key_.to_ullong());
    std::cout << "########################################\n";
    std::cout << "After load key: " << '\n';
    this->_R4_.print();
    std::cout << "########################################\n";
    uploading_the_frame(this->_R4_, this->_frame_.to_ullong());

    for (size_t i = 0; i < 100; ++i) {
        this->__tact__(false);
    }
    for (size_t i = 0; i < 19; ++i) {
        _R1_.set_equation(i, {{std::string("x") + std::to_string(i), 1}});
    }
    for (size_t i = 0; i < 22; ++i) {
        _R2_.set_equation(i, {{std::string("y") + std::to_string(i), 1}});
    }
    for (size_t i = 0; i < 23; ++i) {
        _R3_.set_equation(i, {{std::string("z") + std::to_string(i), 1}});
    }
    
    this->allEquations.clear();
}

std::map<std::string, uint8_t> A5_2::shortening_the_equation(std::map<std::string, uint8_t> equation)
{
    for (auto& monom : equation) {
        monom.second %= 2;
    }
    
    for (auto it = equation.begin(); it != equation.end(); ) {
        if (it->second == 0) {
            it = equation.erase(it);
        } else {
            ++it;
        }
    }
    return equation;
}

std::map<std::string, uint8_t> A5_2::xor_equations(std::map<std::string, uint8_t> lVal, std::map<std::string, uint8_t> rVal)
{
    for(const auto& monom: rVal) {
        lVal[monom.first] += 1;
    }

    return shortening_the_equation(lVal);
}

std::map<std::string, uint8_t> A5_2::multiplay_equations(std::map<std::string, uint8_t> lVal, std::map<std::string, uint8_t> rVal)
{
    std::map<std::string, uint8_t> res;
    for (const auto& lMonom: lVal){
        for(const auto& rMonom: rVal) {
            if(lMonom.first == "1") {
                res[rMonom.first] += 1; 
            }else if(rMonom.first == "1") {
                res[lMonom.first] += 1;
            } else if(lMonom.first == rMonom.first) {
                res[lMonom.first] +=1;
            } else  if(lMonom.first[0] == rMonom.first[0]) {
                uint16_t lIndex = std::stoi(lMonom.first.substr(1, lMonom.first.size() - 1));
                uint16_t rIndex = std::stoi(rMonom.first.substr(1, rMonom.first.size() - 1));;
                if(lIndex <= rIndex) {
                    res[lMonom.first + rMonom.first] += 1;
                } else {
                    res[rMonom.first + lMonom.first] +=1;
                }
            } else if(lMonom.first[0] == 'k') {
                res[lMonom.first + rMonom.first] += 1;
            } else {
                res[rMonom.first + lMonom.first] +=1;
            }
        }
    }
    
    return shortening_the_equation(replaces_monom(res));
}

std::map<std::string, uint8_t> A5_2::replaces_monom(std::map<std::string, uint8_t> source) {
    std::regex regMonom(R"([a-zA-Z]\d+[a-zA-Z]\d+)");
    std::map<std::string, uint8_t> res = {};
    for (auto monom: source) {
        if(std::regex_match(monom.first, regMonom)) {
            if(this->table_of_repleces.find(monom.first) == table_of_repleces.end()) {
                table_of_repleces[monom.first] = std::string("v") + std::to_string(this->countOfReplaces++);
            }
            res[table_of_repleces[monom.first]] += 1;
        } else {
            res[monom.first] += monom.second; 
        }

    }
    
    return shortening_the_equation(res);
}

bool A5_2::__tact__(bool calcEquation)
{   
    std::bitset<17> R4Сondition = this->_R4_.get_bitset();
    std::bitset<3> inputFromR4 = ((R4Сondition[9] << 2) & 0b100) ^ ((R4Сondition[13] << 1) & 0b010) ^ (R4Сondition[6] & 0b001);
    
    bool outputFfromR4 = this->__majority_function__(inputFromR4);
    
    if(outputFfromR4 ^ R4Сondition[6] ^ 0x1) {
        this->_R1_.shift_LSFR();
    }

    if(outputFfromR4 ^ R4Сondition[13] ^ 0x1) {
        this->_R2_.shift_LSFR();
    }

    if(outputFfromR4 ^ R4Сondition[9] ^ 0x1) {
        this->_R3_.shift_LSFR();
    }

    std::bitset<19> R1Сondition = this->_R1_.get_bitset();
    std::bitset<22> R2Сondition = this->_R2_.get_bitset();
    std::bitset<23> R3Сondition = this->_R3_.get_bitset();
    
    std::bitset<3> inputFromR1 = ((R1Сondition[6] << 2) & 0b100) ^ (((R1Сondition[4] << 1) & 0b010) ^ 0b010) ^ R1Сondition[3] & 0b001;
    std::bitset<3> inputFromR2 = ((R2Сondition[12] << 2) & 0b100) ^ ((R2Сondition[8] << 1) & 0b010)  ^ (R2Сondition[5] & 0b001) ^ 0b001;
    std::bitset<3> inputFromR3 = (((R3Сondition[9] << 2) & 0b100) ^ 0b100) ^ ((R3Сondition[6] << 1) & 0b010)  ^ (R3Сondition[4] & 0b001);
    if(calcEquation) {
        std::map<std::string, uint8_t> tmp = {};
        tmp = _R1_.get_equation(14);
        tmp["1"] += 1;
        std::vector<std::map<std::string, uint8_t>> R1equations = {_R1_.get_equation(12), tmp, _R1_.get_equation(15)};
        tmp.clear();
        tmp = _R2_.get_equation(16);
        tmp["1"] += 1;
        std::vector<std::map<std::string, uint8_t>> R2equations = {_R2_.get_equation(9), _R2_.get_equation(13), tmp};
        tmp.clear();
        tmp = _R3_.get_equation(13);
        tmp["1"] += 1;
        std::vector<std::map<std::string, uint8_t>> R3equations = {tmp, _R3_.get_equation(16), _R3_.get_equation(18)};
        this->_R4_.shift_LSFR();    
        
        std::map<std::string, uint8_t> outFofR1 = xor_equations(xor_equations(multiplay_equations(R1equations[0], R1equations[1]), multiplay_equations(R1equations[0], R1equations[2])), multiplay_equations(R1equations[1], R1equations[2])); 
        std::map<std::string, uint8_t> outFofR2 = xor_equations(xor_equations(multiplay_equations(R2equations[0], R2equations[1]), multiplay_equations(R2equations[0], R2equations[2])), multiplay_equations(R2equations[1], R2equations[2])); 
        std::map<std::string, uint8_t> outFofR3 = xor_equations(xor_equations(multiplay_equations(R3equations[0], R3equations[1]), multiplay_equations(R3equations[0], R3equations[2])), multiplay_equations(R3equations[1], R3equations[2])); 

        std::map<std::string, uint8_t> newEquation = xor_equations(xor_equations(xor_equations(xor_equations(xor_equations(_R1_.get_equation(18), _R2_.get_equation(21)), _R3_.get_equation(22)), outFofR1), outFofR2), outFofR3);
        this->allEquations.push_back(newEquation);
    }

    return R1Сondition[0] ^ R2Сondition[0] ^ R3Сondition[0] ^ this->__majority_function__(inputFromR1) ^ this->__majority_function__(inputFromR2) ^ this->__majority_function__(inputFromR3);
}


bool A5_2::__majority_function__(std::bitset<3> input)
{
    return (input[0] & input[1]) ^ (input[0] & input[2]) ^ (input[1] & input[2]);
}

A5_2::A5_2(std::bitset<64> key, std::bitset<22> frame) : _key_{key}, _frame_{frame}
{
    this->__initA5_2__();
}

void A5_2::print_equations()
{
    for (size_t i = 0; i < this->allEquations.size(); ++i)
    {
        std::cout << i << ") ";
        for(auto monom: allEquations[i]) {
            std::cout << monom.first << "+";
        }
        std::cout <<'\n';
    }
    
}

std::bitset<228> A5_2::get_gamma()
{
    std::bitset<228> gamma = 0;
    for (size_t i = 0; i < 228; ++i) {
        gamma ^= this->__tact__(true);
        gamma <<= 1;
    }
    
    return gamma;
}

std::bitset<19> A5_2::get_R1()
{
    return this->_R1_.get_bitset();
}

std::bitset<22> A5_2::get_R2()
{
    return this->_R2_.get_bitset();
}

std::bitset<23> A5_2::get_R3()
{
    return this->_R3_.get_bitset();
}

std::bitset<17> A5_2::get_R4()
{
    return this->_R4_.get_bitset();
}

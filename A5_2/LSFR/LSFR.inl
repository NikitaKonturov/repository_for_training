#ifndef LSFR_INL
#define LSFR_INL
#include "LSFR.hpp"

template <size_t lsfrLenght>
void LSFR<lsfrLenght>::cycle_shift_vector_linear_equations()
{
    std::map<std::string, uint8_t> leftVal = {};
    for(auto iter = polynomDegrees.begin(); iter != this->polynomDegrees.end(); ++iter){
        for(auto monom: linearEquations[*iter]){
            leftVal[monom.first] += 1;
        } 
         
    }

    for (int i = linearEquations.size() - 1; i >= 1; --i) {
        linearEquations[i] = linearEquations[i - 1];
    }

    linearEquations[0] = leftVal;
}

template <size_t lsfrLenght>
void LSFR<lsfrLenght>::cycle_shift_LSFR()
{
    std::bitset<lsfrLenght>leftVal = 0;
    std::bitset<lsfrLenght> mask = 1;
    for(auto iter = polynomDegrees.begin(); iter != polynomDegrees.end(); ++iter){
        leftVal ^= (lsfr >> (lsfr.size() - *iter - 1)) & mask;
    }
    leftVal <<= (lsfrLenght - 1);
    this->lsfr >>= 1;
    this->lsfr ^= leftVal;
}

template <size_t lsfrLenght>
inline std::map<std::string, uint8_t> LSFR<lsfrLenght>::shortening_the_equation(std::map<std::string, uint8_t> equation)
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

template <size_t lsfrLenght>
inline LSFR<lsfrLenght>::LSFR(std::vector<size_t> polynomDegreesSource, std::bitset<lsfrLenght> source)
{
    this->lsfr = source;
    this->linearEquations = std::vector<std::map<std::string, uint8_t>>(lsfr.size());
    if(polynomDegreesSource.size() > lsfrLenght) {
        throw std::runtime_error("The number of degrees of the polynomial must not exceed the LSFR size...");
    }
    std::remove(polynomDegreesSource.begin(), polynomDegreesSource.end(), 0);

    for (size_t i = 0; i < polynomDegreesSource.size(); ++i) {
        if(polynomDegreesSource[i] > lsfrLenght) {
            throw std::runtime_error("The powers of the polynomial must be less than the size of the LSFR...");
        }
        --polynomDegreesSource[i];
    }


    this->polynomDegrees = std::set<size_t>(polynomDegreesSource.begin(), polynomDegreesSource.end());
    return;
}

template <size_t lsfrLenght>
inline LSFR<lsfrLenght>::LSFR(LSFR<lsfrLenght> &source)
{
    this->lsfr = source.lsfr;
    this->linearEquations = source.linearEquations;
    this->polynomDegrees = source.polynomDegrees;
}

template <size_t lsfrLenght>
bool LSFR<lsfrLenght>::shift_LSFR()
{
    bool out = this->lsfr[0];
    this->cycle_shift_LSFR();
    this->cycle_shift_vector_linear_equations();
    this->linearEquations[0] = this->shortening_the_equation(this->linearEquations[0]);
    return out;
}

template <size_t lsfrLenght>
inline void LSFR<lsfrLenght>::add_left_bit(bool bitVal, std::string valName)
{
    std::bitset<lsfrLenght> temp = 0;
    temp ^= bitVal;
    temp = temp << (lsfrLenght - 1);
    this->lsfr ^= temp;
    this->linearEquations[0][valName] = 1;
    this->linearEquations[0] = this->shortening_the_equation(this->linearEquations[0]);
}

template <size_t lsfrLenght>
void LSFR<lsfrLenght>::print()
{
    std::string underLine(18 + lsfrLenght, '_');
    std::string uperLine(18 + lsfrLenght, '-');
    std::cout << uperLine << '\n';
    std::cout << "|LSFR condition: " << this->lsfr << '|' << '\n';
    std::cout << uperLine << '\n';
    std::cout << "The equations: \n";
    for(size_t i = 0; i < this->linearEquations.size(); ++i){
        std::cout << i+1 << ") ";
        for (const auto& monom: linearEquations[i]) {
            std::cout << monom.first << "+";
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

template <size_t lsfrLenght>
inline void LSFR<lsfrLenght>::set_equation(size_t index, std::map<std::string, uint8_t> source)
{
    this->linearEquations[index] = source;
}

template <size_t lsfrLenght>
inline std::bitset<lsfrLenght> LSFR<lsfrLenght>::get_bitset()
{
    return this->lsfr;
}

template <size_t lsfrLenght>
inline std::map<std::string, uint8_t> LSFR<lsfrLenght>::get_equation(size_t index)
{
    return this->linearEquations[index];
}

template <size_t lsfrLenght>
inline void uploading_the_key(LSFR<lsfrLenght> &lsfr, size_t key)
{
    std::string name = "k";
    for (size_t i = 0; i < 64; ++i) {
        lsfr.shift_LSFR();
        lsfr.add_left_bit((key >> (63 - i)) & 1, (name + std::to_string(i)));
    }
}

template <size_t lsfrLenght>
inline void uploading_the_frame(LSFR<lsfrLenght> &lsfr, uint32_t frame)
{
    if(frame > 4194303) {
        throw std::runtime_error("Frame must be less 4194303 (2^22)");
    }

    frame &= 0x003fffff;

    std::string name = "f";
    for (size_t i = 0; i < 22; ++i) {
        lsfr.shift_LSFR();
        lsfr.add_left_bit((frame >> (21 - i)) & 1, (name + std::to_string(i)));
    }

}

#endif //LSFR_INL

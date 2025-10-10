#ifndef LSFR_INL
#define LSFR_INL
#include "LSFR.hpp"

template <size_t lsfrLenght>
void LSFR<lsfrLenght>::cycle_shift_vector_linear_equations()
{
    std::string leftVal = "";
    for(auto iter = polynomDegrees.begin(); iter != this->polynomDegrees.end(); ++iter){
        if(linearEquations[*iter] != "") {
            if(leftVal != ""){
                leftVal += "+";
            } 
            leftVal += linearEquations[*iter];
        } 
    }

    for (int i = 0; i < linearEquations.size() - 1; ++i) {
        linearEquations[i] = linearEquations[i + 1];
    }

    linearEquations[linearEquations.size() - 1] = leftVal;
}

template <size_t lsfrLenght>
void LSFR<lsfrLenght>::cycle_shift_SR()
{
    std::bitset<lsfrLenght>leftVal = 0;
    std::bitset<lsfrLenght> mask = 1;
    for(auto iter = polynomDegrees.begin(); iter != polynomDegrees.end(); ++iter){
        leftVal ^= (lsfr >> (lsfr.size() - *iter - 1)) & mask;
    }
    this->lsfr <<= 1;
    this->lsfr ^= leftVal;
}

template <size_t lsfrLenght>
inline std::string LSFR<lsfrLenght>::shortening_the_equation(std::string equation)
{
    std::regex plusReg("\\+");
    std::unordered_map<std::string, size_t> varsCount;
    std::sregex_token_iterator iter(equation.cbegin(), equation.cend(), plusReg, -1);
    for(std::sregex_token_iterator end; iter != end; ++iter){
        std::string var = *iter;
        if(varsCount.find(var) != varsCount.end()){
            ++varsCount[var];
        }
        else {
            varsCount[var] = 1;
        }
    }   

    std::string resEquation = "";
    
    for(auto varCount: varsCount){
        if(varCount.second & 0x0001) {
            if(resEquation != "") {
                resEquation.push_back('+');
            }
            resEquation.append(varCount.first);
        }
    }

    return resEquation;
}

template <size_t lsfrLenght>
inline LSFR<lsfrLenght>::LSFR(std::vector<size_t> polynomDegreesSource, uint64_t initFilling)
{
    // Заполняем нулями
    this->lsfr = initFilling;
    // создаём заготовки для уравнений
    this->linearEquations = std::vector<std::string>(lsfr.size(), "");
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
    this->cycle_shift_SR();
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
    if(linearEquations[0] != "") {
        this->linearEquations[0].append("+");
    }
    this->linearEquations[0].append(valName);
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
    // std::cout << "The equations: \n";
    // for(size_t i = 0; i < this->linearEquations.size(); ++i){
    //     if(linearEquations[i] != "")
    //         std::cout << i << ") " << linearEquations[i] << std::endl;
    // }
    // std::cout << std::endl;
}

template<size_t lsfrLenght>
bool LSFR<lsfrLenght>::operator[](size_t index) 
{
    if(index >= lsfrLenght) {
        throw std::invalid_argument("Invalid index");
    }
    return this->lsfr[index];
}



template <size_t lsfrLenght>
inline void uploading_the_key(LSFR<lsfrLenght> &lsfr, size_t key)
{
    std::string name = "(k";
    for (size_t i = 0; i < 64; ++i) {
        lsfr.shift_LSFR();
        lsfr.add_left_bit((key >> (63 - i)) & 1, (name + std::to_string(i) + ')'));
        if(i + 1 >=18 && i + 1 <= 23) {
            std::cout << i + 1 << '\n';
            lsfr.print();
        }
    }
}

template <size_t lsfrLenght>
inline void uploading_the_frame(LSFR<lsfrLenght> &lsfr, uint32_t frame)
{
    if(frame > 4194303) {
        throw std::runtime_error("Frame must be less 4194303 (2^22)");
    }

    frame &= 0x003fffff;

    std::string name = "(f";
    for (size_t i = 0; i < 22; ++i) {
        lsfr.shift_LSFR();
        lsfr.add_left_bit((frame >> (21 - i)) & 1, (name + std::to_string(i) + ')'));
    }

}

#endif //LSFR_INL

#ifndef SR_INL
#define SR_INL
#include "SR.hpp"

// template <size_t srLenght>
// void SR<lsfrLenght>::cycle_shift_vector_linear_equations()
// {
//     std::string leftVal = "";
//     for(auto iter = polynomDegrees.begin(); iter != this->polynomDegrees.end(); ++iter){
//         if(linearEquations[*iter] != "") {
//             if(leftVal != ""){
//                 leftVal += "+";
//             } 
//             leftVal += linearEquations[*iter];
//         } 
//     }

//     for (int i = 0; i < linearEquations.size() - 1; ++i) {
//         linearEquations[i] = linearEquations[i + 1];
//     }

//     linearEquations[linearEquations.size() - 1] = leftVal;
// }

template <size_t srLenght>
void SR<srLenght>::cycle_shift_SR()
{
    std::bitset<srLenght>leftVal = funck(this->sr);
    this->sr <<= 1;    
    this->sr ^= leftVal;
}

// template <size_t srLenght>
// inline std::string SR<lsfrLenght>::shortening_the_equation(std::string equation)
// {
//     std::regex plusReg("\\+");
//     std::unordered_map<std::string, size_t> varsCount;
//     std::sregex_token_iterator iter(equation.cbegin(), equation.cend(), plusReg, -1);
//     for(std::sregex_token_iterator end; iter != end; ++iter){
//         std::string var = *iter;
//         if(varsCount.find(var) != varsCount.end()){
//             ++varsCount[var];
//         }
//         else {
//             varsCount[var] = 1;
//         }
//     }   

//     std::string resEquation = "";
    
//     for(auto varCount: varsCount){
//         if(varCount.second & 0x0001) {
//             if(resEquation != "") {
//                 resEquation.push_back('+');
//             }
//             resEquation.append(varCount.first);
//         }
//     }

//     return resEquation;
// }

template <size_t srLenght>
inline SR<srLenght>::SR(std::bitset<srLenght>(*applyFunck)(std::bitset<srLenght>), uint64_t initFilling)
{
    this->sr = initFilling;
    this->funck = applyFunck;
    return;
}

template <size_t srLenght>
inline SR<srLenght>::SR(SR<srLenght> &source)
{
    this->sr = source.sr;
    this->funck = source.funck;
}

template <size_t srLenght>
bool SR<srLenght>::shift_SR()
{
    bool out = this->sr[0];
    this->cycle_shift_SR();
    return out;
}

// template <size_t srLenght>
// inline void SR<lsfrLenght>::add_left_bit(bool bitVal, std::string valName)
// {
//     std::bitset<lsfrLenght> temp = 0;
//     temp ^= bitVal;
//     temp = temp << (srLenght - 1);
//     this->sr ^= temp;
//     if(linearEquations[0] != "") {
//         this->linearEquations[0].append("+");
//     }
//     this->linearEquations[0].append(valName);
//     this->linearEquations[0] = this->shortening_the_equation(this->linearEquations[0]);
// }

template <size_t srLenght>
void SR<srLenght>::print()
{
    std::string underLine(18 + srLenght, '_');
    std::string uperLine(18 + srLenght, '-');
    std::cout << uperLine << '\n';
    std::cout << "|SR condition: " << this->sr << '|' << '\n';
    std::cout << uperLine << '\n';
    // std::cout << "The equations: \n";
    // for(size_t i = 0; i < this->linearEquations.size(); ++i){
    //     if(linearEquations[i] != "")
    //         std::cout << i << ") " << linearEquations[i] << std::endl;
    // }
    // std::cout << std::endl;
}

template <size_t srLenght>
inline bool SR<srLenght>::operator[](size_t index)
{
    if(index >= srLenght) {
        throw std::invalid_argument("Invalid index...");
    }
    return this->sr[index];
}

template <size_t srLenght>
inline void uploading_the_key(SR<srLenght> &lsfr, size_t key)
{
    std::string name = "(k";
    for (size_t i = 0; i < 64; ++i) {
        lsfr.shift_SR();
        lsfr.add_left_bit((key >> (63 - i)) & 1, (name + std::to_string(i) + ')'));
        if(i + 1 >=18 && i + 1 <= 23) {
            std::cout << i + 1 << '\n';
            lsfr.print();
        }
    }
}

template <size_t srLenght>
inline void uploading_the_frame(SR<srLenght> &lsfr, uint32_t frame)
{
    if(frame > 4194303) {
        throw std::runtime_error("Frame must be less 4194303 (2^22)");
    }

    frame &= 0x003fffff;

    std::string name = "(f";
    for (size_t i = 0; i < 22; ++i) {
        lsfr.shift_SR();
        lsfr.add_left_bit((frame >> (21 - i)) & 1, (name + std::to_string(i) + ')'));
    }

}

#endif //SR_INL

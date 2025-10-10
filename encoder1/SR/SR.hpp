#ifndef SR_CLASS
#define SR_CLASS 
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <stdint.h>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <vector>
#include <string>
#include <bitset>
#include <regex>
#include <set>


template<size_t srLenght>
class SR {
private:
    std::bitset<srLenght> sr;
    std::function<std::bitset<srLenght>(std::bitset<srLenght>)> funck;
    // std::vector<std::string> linearEquations;
    // std::set<size_t> polynomDegrees; 
    // void cycle_shift_vector_linear_equations();
    void cycle_shift_SR();
    // std::string shortening_the_equation(std::string equation);
public:
    SR(std::bitset<srLenght>(*applyFunck)(std::bitset<srLenght>), uint64_t initFilling = 0);
    SR(SR<srLenght>& source);
    bool shift_SR();
    // void add_left_bit(bool bitVal, std::string valName = "");
    ~SR() = default;
    void print();
    bool operator[](size_t index);
};

// Загрузка ключа в РСЛОС
template<size_t srLenght>
void uploading_the_key(SR<srLenght> & lsfr, size_t key);

// Загрузка номера кадра
template<size_t srLenght>
void uploading_the_frame(SR<srLenght> & lsfr, uint32_t frame);

#include "SR.inl"
#endif // SR_CLASS


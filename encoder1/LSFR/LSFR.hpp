#ifndef LSFR_CLASS
#define LSFR_CLASS 
#include <unordered_map>
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


template<size_t lsfrLenght>
class LSFR {
private:
    std::bitset<lsfrLenght> lsfr;
    std::vector<std::string> linearEquations;
    std::set<size_t> polynomDegrees; 
    void cycle_shift_vector_linear_equations();
    void cycle_shift_SR();
    std::string shortening_the_equation(std::string equation);
public:
    LSFR(std::vector<size_t> polynomDegreesSource, uint64_t initFilling = 0);
    LSFR(LSFR<lsfrLenght>& source);
    bool shift_LSFR();
    void add_left_bit(bool bitVal, std::string valName = "");
    ~LSFR() = default;
    void print();
    bool operator[](size_t index);
};

// Загрузка ключа в РСЛОС
template<size_t lsfrLenght>
void uploading_the_key(LSFR<lsfrLenght> & lsfr, size_t key);

// Загрузка номера кадра
template<size_t lsfrLenght>
void uploading_the_frame(LSFR<lsfrLenght> & lsfr, uint32_t frame);

#include "LSFR.inl"
#endif // LSFR_CLASS


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
#include <map>


template<size_t lsfrLenght>
class LSFR {
private:
    std::bitset<lsfrLenght> lsfr;
    std::vector<std::map<std::string, uint8_t>> linearEquations;
    std::set<size_t> polynomDegrees; 
    void cycle_shift_vector_linear_equations();
    void cycle_shift_LSFR();
    std::map<std::string, uint8_t> shortening_the_equation(std::map<std::string, uint8_t> equation);
public:
    LSFR(std::vector<size_t> polynomDegreesSource, std::bitset<lsfrLenght> source);
    LSFR(LSFR<lsfrLenght>& source);
    bool shift_LSFR();
    void add_left_bit(bool bitVal, std::string valName = "");
    ~LSFR() = default;
    void print();
    void set_equation(size_t index, std::map<std::string, uint8_t> source);
    std::bitset<lsfrLenght> get_bitset();
    std::map<std::string, uint8_t> get_equation(size_t index);
};

// Загрузка ключа в РСЛОС
template<size_t lsfrLenght>
void uploading_the_key(LSFR<lsfrLenght> & lsfr, size_t key);

// Загрузка номера кадра
template<size_t lsfrLenght>
void uploading_the_frame(LSFR<lsfrLenght> & lsfr, uint32_t frame);

#include "LSFR.inl"
#endif // LSFR_CLASS


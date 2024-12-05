
#ifndef FUNCS_HPP
#define FUNCS_HPP
#include<iostream>
#include<vector>
#include<math.h>
#include<mutex>
#include<thread>

char16_t multiplicateBinMtrx(char16_t, char16_t);
char16_t createHASH(const std::string&);
char16_t parity16(char16_t);
void printBinVariable(char16_t);
size_t factotial(size_t);

// Генерация всех перстановок просто для эллементов
constexpr void generatePermutation(size_t, std::vector<std::vector<size_t>>&);
constexpr int64_t findIndexOfMaxMobileElement(const std::vector<size_t>&, const std::vector<int>&);
constexpr void swapEllement(std::vector<size_t>&, std::vector<int>& , size_t, size_t);
constexpr void changeDerection(const std::vector<size_t>&, std::vector<int>&, size_t);

#include "funcs.inl"

#endif //FUNCS_HPP

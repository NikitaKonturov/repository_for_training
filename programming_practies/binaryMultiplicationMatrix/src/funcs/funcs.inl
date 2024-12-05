
#include "funcs.hpp"
#define SHIFT(i, let) ((let>>(i*4)) & (0xf))
#define COST_MTRX 0xa5a5

// size_t factotial(size_t num) 
// {
//     size_t res = 1;
//     for (size_t i = 1; i <= num; ++i) {
//         res *= i; 
//     }
//     return res;
// }

// char16_t parity16(char16_t let)
// {
//     let ^= (let >> 8);
//     let ^= (let >> 4);
//     let ^= (let >> 2);
//     let ^= (let >> 1);

//     return let & 0x0001;
// }

// char16_t multiplicateBinMtrx(char16_t first, char16_t second)
// {
//     char16_t result = 0x0000;
//     char16_t mixedBits = 0x0000;
    
//     // матрица полученная перемешиванием битов другой матрицы(её можно использовать как отдеельную хеш функию)
//     size_t k = 15;
//     for (int i = 3; i >= 0; --i) {
//         for (int j = 3; j >= 0; --j) {
//             mixedBits |= parity16(first >> i & second >> j & 0x000f) << k--;       
//         }
//     }
    
//     k = 15;
//     // пермножение первой и второй матрицы с добавлением битов из перемешеной
//     first |= 0xff00;
//     second |= 0xff00;
//     for (int i = 3; i >= 0; --i) {
//         for (int j = 3; j >= 0; --j) {
//             result |= parity16(SHIFT(i, second) & SHIFT(j, first) & 0x000f) << k--;       
//         }
//     }
    
//     return result;
// }

// char16_t createHASH(const std::string& text)
// {
//     char16_t hash = static_cast<char16_t>(text[0]);
//     char16_t const_mtrx = 0xa5a5;
//     for (size_t i = 1; i < text.size(); ++i) {
//         hash = multiplicateBinMtrx(hash, static_cast<char16_t>(text[i]));
//         //hash = multiplicateBinMtrx(hash, const_mtrx);
//         //std::cout << "hash " << text[i] << " = ";
//     }
    
//     return hash;
// }

// void printBinVariable(char16_t source)
// {
//     for (int32_t i = 15; i >= 0; --i) {
//         if((source >> i) & 1) {
//             std::cout << 1 << " ";
//         } 
//         else {
//             std::cout << 0 << " "; 
//         }
//     }
// }


// #################################################################
// Создание всех перестановок



constexpr int64_t findIndexOfMaxMobileElement(std::vector<size_t>& permutation,const std::vector<int>& direction)
{
    int64_t index = -1;
    for (size_t i = 0; i < permutation.size(); ++i) {
        if(((i + direction[i]) >= 0) && ((i + direction[i]) < permutation.size())) {
            if(permutation[i] > permutation[i + direction[i]]) {
                if(index == -1) {
                    index = i;
                }
                else if(permutation[i] > permutation[index]) {
                    index = i;
                }
            }
        }    
    }

    return index;
}

// можно передавать и один указатель на максимально мобильный эллемнт но оставим два для более наглядного представления алгоритма в главнной функции 
constexpr void swapEllements(std::vector<size_t>& permutation, std::vector<int>& direction, size_t indexToMaxMobileEllement, size_t indexToIndicatedEllement)
{
    std::swap(permutation[indexToMaxMobileEllement], permutation[indexToIndicatedEllement]);
    std::swap(direction[indexToMaxMobileEllement], direction[indexToIndicatedEllement]);
}

constexpr void changeDerection(const std::vector<size_t>& permutation , std::vector<int>& direction, size_t maxMobileEllement)
{
    for (size_t i = 0; i < permutation.size(); ++i) {
        if(permutation[i] > maxMobileEllement) {
            direction[i] *= -1;
        }
    }
}


constexpr void generatePermutation(size_t size, std::vector<std::vector<size_t>>& permutations)
{
    // создаём вектор указателей на эллементы -1(указатель влево) 1 (вправо)
    std::vector<int> direction(size, -1);
    // созздаём вектор самих элементов(изначально перестановка тривиальная)
    std::vector<size_t> permutation(size);
    for (size_t i = 0; i < size; ++i) {
        permutation[i] = i + 1;
    }

    int64_t indexToMaxMobileEllem = findIndexOfMaxMobileElement(permutation, direction);
    size_t maxMobileEllem = 0;
    size_t j = 0;
    while (indexToMaxMobileEllem != -1) {
        maxMobileEllem = permutation[indexToMaxMobileEllem];
        swapEllements(permutation, direction, indexToMaxMobileEllem, direction[indexToMaxMobileEllem] + indexToMaxMobileEllem);
        changeDerection(permutation, direction, maxMobileEllem);
        indexToMaxMobileEllem = findIndexOfMaxMobileElement(permutation, direction);
        permutations.push_back(permutation);
    }
}

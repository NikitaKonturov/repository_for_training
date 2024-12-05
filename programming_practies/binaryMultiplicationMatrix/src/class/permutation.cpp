#include"permutation.hpp"


Permutation::Permutation(size_t sizeOfPermutation)
{
    // создаём вектор указателей на эллементы -1(указатель влево) 1 (вправо)
    std::vector<int> direction(sizeOfPermutation, -1);
    // созздаём вектор самих элементов(изначально перестановка тривиальная)
    std::vector<size_t> permutation(sizeOfPermutation);
    for (size_t i = 0; i < sizeOfPermutation; ++i) {
        permutation[i] = i + 1;
    }

    




}
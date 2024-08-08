#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP
#include<iostream>
#include<vector>


class Permutation
{
private:
    std::vector<std::vector<size_t>> allPermutations;

    int64_t findIndexOfMaxMobileElement(const std::vector<size_t>&, const std::vector<int>&);
    void swapEllement(std::vector<size_t>&, std::vector<int>& , size_t, size_t);
    void changeDerection(const std::vector<size_t>&, std::vector<int>&, size_t);
public:
    Permutation(size_t);
    ~Permutation() = default;

    std::vector<size_t>& operator[](size_t);
};




#endif //PERMUTATION
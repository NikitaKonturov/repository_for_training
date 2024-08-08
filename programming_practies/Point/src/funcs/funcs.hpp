#ifndef FUNCS_HPP
#define FUNCS_HPP

#include <iostream>
#include <fstream>
#include "../TV/television.hpp"


template<char del>
void writeToBin(std::ofstream&, const TV<del>&);

template<char del>
void readFromBin(std::ifstream&, TV<del>&);


#include"funcs.inl"

#endif

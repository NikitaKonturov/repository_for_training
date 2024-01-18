#ifndef _FUNCS_HPP_
#define _FUNCS_HPP_
#include <iostream>
#include <string>
#include <vector>

size_t getNumberOfVisier(std::string path);
std::vector<std::pair<double, double>> getVectorWithTime(std::string path);
size_t countOfMaxPersons(std::vector<std::pair<double, double>> arr);



#endif
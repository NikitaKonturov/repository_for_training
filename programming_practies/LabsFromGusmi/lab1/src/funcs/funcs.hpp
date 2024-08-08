
#ifndef FUNCS_HPP
#define FUNCS_HPP
#include<iostream>
#include<filesystem>
#include <nlohmann/json.hpp>
#include<format>


void CheckArgumentsAmount(int); 
void CheckInputPath(const std::filesystem::path&);
bool IsJsonCorrect(const nlohmann::json&);

#endif //FUNCS_HPP

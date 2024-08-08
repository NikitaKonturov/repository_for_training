
#ifndef FUNCS_HPP
#define FUNCS_HPP
#include<iostream>
#include<filesystem>
#include<format>
#include<fstream>
#include<nlohmann/json.hpp>
#include<ctime>


void CheckArgumentsAmount(int);
void CheckInputPath(const std::filesystem::path&);
tm GetRequiredDateTime();
nlohmann::json TmToJson(tm);

#endif //FUNCS_HPP

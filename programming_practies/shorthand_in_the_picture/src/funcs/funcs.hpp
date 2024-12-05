#ifndef FUNCS_HPP
#define FUNCS_HPP
#include<format>
#include<fstream>
#include<iostream>
#include<filesystem>


void CheckArgumentsAmount(int); 
void CheckInputPath(const std::filesystem::path&);
void creatImageWithText(std::ifstream&, std::ofstream&, std::string&);

#endif //FUNCS_HPP

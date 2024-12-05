
#ifndef FUNCS_HPP
#define FUNCS_HPP
#include<iostream>
#include<nlohmann/json.hpp>
#include<filesystem>
#include<fstream>
#include<format>
#include<sstream>
#include <algorithm>

void CheckArgumentsAmount(int arguments_amount);
void CheckInputPath(const std::filesystem::path& path_to_filesysteam_object);
void ModifyJsonObject(nlohmann::json& json_object);
void GenerateFiles(char* path);

#endif //FUNCS_HPP

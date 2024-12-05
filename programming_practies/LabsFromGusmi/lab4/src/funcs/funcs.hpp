
#ifndef FUNCS_HPP
#define FUNCS_HPP
#include<format>
#include<fstream>
#include<iostream>
#include<iterator>
#include<filesystem>
#include<nlohmann/json.hpp>


void CheckArgumentsAmount(int argument_amount);
void CheckInputPath(const std::filesystem::path& path_to_filesystem_object);

std::size_t Size(const std::filesystem::path& path_to_filesystem_object); 
size_t GetObjectAmount(const std::filesystem::path& path_to_directory, bool pred(std::filesystem::directory_iterator&));

nlohmann::json GetRegularFileInfo(const std::filesystem::path& path_to_file);
nlohmann::json GetDirectoryInfo(const std::filesystem::path& path_to_directory);
nlohmann::json GetFsObjectInfo(const std::filesystem::path& path_to_filesystem_object);

#endif //FUNCS_HPP

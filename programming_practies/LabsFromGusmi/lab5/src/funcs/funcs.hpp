
#ifndef FUNCS_HPP
#define FUNCS_HPP
#include<format>
#include<iomanip>
#include<iostream>
#include<filesystem>


void CheckArgumentsAmount(int); 
void CheckInputPath(const std::filesystem::path&);
std::size_t Size(const std::filesystem::path&);

namespace filesystem_object {
    struct Info {
        std::string name;
        std::string type;
        size_t size;
        std::filesystem::path path_to_directory;
    };
}
std::ostream& operator<<(std::ostream&, const filesystem_object::Info&);

#endif //FUNCS_HPP

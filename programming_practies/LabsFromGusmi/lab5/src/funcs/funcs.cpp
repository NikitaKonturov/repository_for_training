#include "funcs.hpp"


void CheckArgumentsAmount(int arguments_amount) 
{
    if(arguments_amount != 2) {
        throw std::invalid_argument(std::format("Invalid command line arguments amount: current {}, required {}", arguments_amount, 2));
    }
}

void CheckInputPath(const std::filesystem::path& path_to_filesystem_object)
{
    if (!std::filesystem::exists(path_to_filesystem_object)) {    
        throw std::invalid_argument(std::format("Filesystem object by path {} is not exists!", std::filesystem::absolute(path_to_filesystem_object).string()));
    }
    if (!std::filesystem::is_directory(path_to_filesystem_object)) {
        throw std::invalid_argument(std::format("Filesystem object by path {} is not a directory!", std::filesystem::absolute(path_to_filesystem_object).string()));
    }
}

std::size_t Size(const std::filesystem::path& path_to_filesystem_object)
{
    size_t size;
    std::filesystem::recursive_directory_iterator iter(path_to_filesystem_object);
    std::filesystem::recursive_directory_iterator end;

    for(std::filesystem::recursive_directory_iterator iter(path_to_filesystem_object), end; iter != end; ++iter) {
        if(std::filesystem::is_directory(*iter)) {
            size += std::filesystem::file_size(*iter);
        }
    }

    return size;
}

std::ostream& operator<<(std::ostream& out, const filesystem_object::Info& source)
{
    std::setfill(" ");
    out << "Path to directory: " << std::left  << std::setw(50)  << source.path_to_directory << std::endl;
    out << "Name: " << std::left << std::setw(20) << source.name << std::endl;
    out << "Type: " << std::left << std::setw(20) << source.type << std::endl;
    out << "Size: " << std::left << std::setw(20) << source.size << std::endl;

    return out;
}

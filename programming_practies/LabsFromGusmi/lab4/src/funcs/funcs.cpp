#include "funcs.hpp"


void CheckArgumentsAmount(int argument_amount)
{
    if(argument_amount != 2) {
        throw std::invalid_argument(std::format("Invalid command line arguments amount: current – {}, required – {}", argument_amount, 2));
    }

    std::cout << "The number of arguments is correct!" << std::endl;
}

void CheckInputPath(const std::filesystem::path& path_to_filesystem_object)
{
    if(!std::filesystem::exists(path_to_filesystem_object)) {
        throw std::invalid_argument(std::format("Filesystem object by path {} is not exists!", std::filesystem::absolute(path_to_filesystem_object).string()));
    }
    if(!std::filesystem::is_regular_file(path_to_filesystem_object) && !std::filesystem::is_directory(path_to_filesystem_object)) {
        throw std::invalid_argument(std::format("Filesystem object by path {} has invalid type!", std::filesystem::absolute(path_to_filesystem_object).string()));
    }

    std::cout << "Inupt path is correct!" << std::endl;
}    

std::size_t Size(const std::filesystem::path& path_to_filesystem_object)
{
    size_t size = 0;
    if(std::filesystem::is_directory(path_to_filesystem_object)){
        for(std::filesystem::directory_entry dir_entre : std::filesystem::recursive_directory_iterator(path_to_filesystem_object)) {
            if(dir_entre.is_regular_file()) {
                size += dir_entre.file_size();
            }
        }
        return size;
    }
    else {
        return std::filesystem::file_size(path_to_filesystem_object);
    }
}

size_t GetObjectAmount(const std::filesystem::path& path_to_directory, bool pred(std::filesystem::directory_entry&))
{
    size_t amount = 0;

    for (std::filesystem::directory_entry dir_obj : std::filesystem::directory_iterator(path_to_directory)) {
        if(pred(dir_obj)) {
            ++amount;
        }
    }

    return amount;
}

nlohmann::json GetRegularFileInfo(const std::filesystem::path& path_to_file)
{
    nlohmann::json info;
    info["type"] = "regular_file";
    info["full_name"] = path_to_file.filename().string() + path_to_file.extension().string();
    info["name_without_extension"] = path_to_file.stem().string();
    info["extension"] = (path_to_file.has_extension() ?  path_to_file.extension().string() : NULL);
    info["size"] = Size(path_to_file);
}

nlohmann::json GetDirectoryInfo(const std::filesystem::path& path_to_directory)
{
    nlohmann::json info;
    info["type"] = "directory";
    info["name"] = path_to_directory.stem();
    info["size"] = Size(path_to_directory);
    info["files_amount"] = GetObjectAmount(path_to_directory, [](std::filesystem::directory_entry& dir_obj) {return dir_obj.is_regular_file();});
    info["directories_amount"] = GetObjectAmount(path_to_directory, [](std::filesystem::directory_entry& dir_obj) {return dir_obj.is_directory();});

    return info;
}


nlohmann::json GetFsObjectInfo(const std::filesystem::path& path_to_filesystem_object)
{
    nlohmann::json info;
    info = (std::filesystem::is_directory(path_to_filesystem_object) ? GetDirectoryInfo(path_to_filesystem_object): GetRegularFileInfo(path_to_filesystem_object));

    return info;
}

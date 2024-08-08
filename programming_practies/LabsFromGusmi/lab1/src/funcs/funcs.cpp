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
    if (!std::filesystem::is_regular_file(path_to_filesystem_object)) {
        throw std::invalid_argument(std::format("Filesystem object by path {} is not a regular file!", std::filesystem::absolute(path_to_filesystem_object).string()));
    }
    if (!path_to_filesystem_object.has_extension() || path_to_filesystem_object.extension() != std::filesystem::path(".json")) {
        throw std::invalid_argument(std::format("Filesystem object by path {} has invalid extension!", std::filesystem::absolute(path_to_filesystem_object).string()));
    }
}

bool IsJsonCorrect(const nlohmann::json& json)
{
// Проверка объекта на пустоту 
    if (json.empty()) {
        return false;
    }    
    nlohmann::json jsonTemplate = nlohmann::json::parse(R"(
    {
        "string_0" : "some string",
        "number" : 10,
        "object" :
        {
            "boolean" : true,
            "array" : []
        },
        "string_1" : null,
        "array" : null
    })"); 
    
    for (nlohmann::json::iterator i = jsonTemplate.begin(); i != jsonTemplate.end(); ++i) {
        if (json.find(i.key().c_str()) == json.end() || json.find(i.key().c_str()).value() != i.value()){
            return false;
        }
    }
    
    return true;
}

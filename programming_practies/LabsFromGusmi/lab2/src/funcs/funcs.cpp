#include "funcs.hpp"


void CheckArgumentsAmount(int arguments_amount)
{
    if (arguments_amount != 2) {
        throw std::invalid_argument(std::format("Invalid command line arguments amount: current {}, required {}", arguments_amount, 2));
    }
}

void CheckInputPath(const std::filesystem::path& path_to_filesysteam_object)
{
    if(!std::filesystem::exists(path_to_filesysteam_object)) {
        throw std::invalid_argument(std::format("Filesystem object by path: {} is not exists!", std::filesystem::absolute(path_to_filesysteam_object).string()));
    }
    if(!std::filesystem::is_regular_file(path_to_filesysteam_object)) {
        throw std::invalid_argument(std::format("Filesystem object by path: {} is not a regular file!", std::filesystem::absolute(path_to_filesysteam_object).string()));
    }
    if(!path_to_filesysteam_object.has_extension() || path_to_filesysteam_object.extension() != std::filesystem::path(".json")) {
        throw std::invalid_argument(std::format("Filesystem object by path {} has invalid extension!", std::filesystem::absolute(path_to_filesysteam_object).string()));
    }
}

void ModifyJsonObject(nlohmann::json& json_object) 
{
    nlohmann::json::iterator endForMainObject = json_object.end();
    nlohmann::json::iterator endForCheckingObject = nlohmann::json::iterator();
    nlohmann::json correct;
    size_t count = 0;

    for (nlohmann::json::iterator i = json_object.begin(); i != endForMainObject; ++i) {
        count = 0;
        if(i.value().is_object()) {
            count = std::count_if(i->begin(), i->end(), [](nlohmann::json& item) {return item.is_object();});
        }

        if (count < 3) {
            correct[i.key()] = i.value();
        }
    }

    json_object = correct;
}

void GenerateFiles(char* path)
{
    std::filesystem::path pathToFile(path);
    CheckInputPath(pathToFile);
    nlohmann::json mainObject = nlohmann::json::parse(std::ifstream(path));
    nlohmann::json::iterator end = mainObject.end();
    std::ofstream fout;
    for (nlohmann::json::iterator i = mainObject.begin(); i != end; ++i) {
        if(i.value().is_object()) {
            ModifyJsonObject(i.value());
            fout.open((std::filesystem::absolute(pathToFile).parent_path().string()) + "/" + i.key() + ".json");
            fout << i.value().dump(4);
            std::cout << "File is write..." << std::endl;
            fout.close();
        }
    }

}
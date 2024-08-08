
#include "../funcs/funcs.hpp"
#include <fstream>
#include <nlohmann/json.hpp>


int main(int args, char* argv[]) {
    try {
        CheckArgumentsAmount(args);
        std::filesystem::path path(argv[1]);
        CheckInputPath(path);
        if (IsJsonCorrect(nlohmann::json::parse(std::ifstream(path.c_str())))) {
            std::cout << "true" << std::endl;
        }
        else {
            std::cout << "false" << std::endl;
        }
    }
    catch(std::invalid_argument &err) {
        std::cerr << err.what() << std::endl;
    }
}
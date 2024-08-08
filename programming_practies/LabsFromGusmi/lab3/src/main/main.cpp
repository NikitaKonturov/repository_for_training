
#include "../funcs/funcs.hpp"


int main(int args, char* argv[])
{
    try {
    CheckArgumentsAmount(args);
    tm time = GetRequiredDateTime();
    
    nlohmann::json jsTime = TmToJson(time);
    std::cout << jsTime.dump(4) << std::endl;
    CheckInputPath(argv[1]);
    std::filesystem::path parentPath = std::filesystem::path(argv[1]).parent_path(); 
    if(std::filesystem::exists(parentPath)) {
        std::filesystem::create_directories(parentPath);
    }
    
    std::ofstream fout(argv[1]);
    fout << jsTime.dump(4) << std::endl;
    }
    catch(std::invalid_argument& err) {
        std::cerr << "Invalid argument: " << err.what() << std::endl;
    }
    
    return 0;
}

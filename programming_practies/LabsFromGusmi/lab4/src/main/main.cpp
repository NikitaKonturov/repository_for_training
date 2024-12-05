
#include "../funcs/funcs.hpp"


int main(int args, char** argv)
{
    try {
        CheckArgumentsAmount(args);
        
        std::filesystem::path path_to_filesystem_object(argv[1]);
        CheckInputPath(path_to_filesystem_object);
        std::string path_to_file_with_info = path_to_filesystem_object.parent_path().string() + "/fs_object_info.json";
        std::ofstream fout(path_to_file_with_info);

        fout << GetFsObjectInfo(path_to_filesystem_object).dump(4) << std::endl;
        
        fout.close();

        std::cout << "The information is written to a file: " << path_to_file_with_info << std::endl;
    }
    catch(nlohmann::json::exception& err) {
        std::cerr << "Nlohmann json: " << err.what() << std::endl;
    }
    catch(std::filesystem::filesystem_error& err) {
        std::cerr << "Filesystem error: " << err.what() << std::endl;
    }
    catch(std::invalid_argument& err) {
        std::cerr << "Invalid argument: " << err.what() << std::endl;
    }
    catch(const std::exception& err) {
        std::cerr << err.what() << '\n';
    }
    return 0;
}

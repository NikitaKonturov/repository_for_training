/* ================================ Вариант №9 ================================*/


#include "../funcs/funcs.hpp"


int main(int args, char* argv[])
{
    try {
    CheckArgumentsAmount(args);
    CheckInputPath(argv[1]);
    GenerateFiles(argv[1]);
    }
    catch(std::invalid_argument& err) {
        std::cerr << "Invalid_argument: " << err.what() << std::endl;
    }
    catch(nlohmann::json_abi_v3_11_3::detail::parse_error &err) {
        std::cerr << "Parse error" << err.what() << std::endl;
    }
    catch(nlohmann::json_abi_v3_11_3::detail::type_error &err) {
        std::cerr << "Type error: " << err.what() << std::endl;
    }
    return 0;
}

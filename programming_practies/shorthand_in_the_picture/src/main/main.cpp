#include "../funcs/funcs.hpp"


int main(int args, char* argv[])
{
    try {
        CheckArgumentsAmount(args);
        std::filesystem::path inputImegPath(argv[1]);
        CheckInputPath(inputImegPath);

        std::string mes = "Hellow world";

        if(std::filesystem::file_size(inputImegPath) / 8 <  (mes.size() * sizeof(char))) {
            throw std::invalid_argument("Invalid message size...");
        }        

        std::string pathToNewImage = inputImegPath.parent_path().string() + "/newImage.jpg";

        std::ifstream fin(inputImegPath.string(), std::ios::binary);
        std::ofstream fout(pathToNewImage, std::ios::binary);

        creatImageWithText(fin, fout, mes);
    }
    catch(std::invalid_argument &err) {
        std::cerr << "\033[31m" << "Invalid argument: " << err.what() << "\033[0m" << std::endl;
    }
    catch(std::exception err) {
        std::cerr << "\033[31m" << "Anny exception: " << err.what() << "\033[0m" << std::endl;     
    }
    return 0;
}

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
    if (!path_to_filesystem_object.has_extension() || path_to_filesystem_object.extension() != std::filesystem::path(".jpg")) {
        throw std::invalid_argument(std::format("Filesystem object by path {} has invalid extension!", std::filesystem::absolute(path_to_filesystem_object).string()));
    }
}

void creatImageWithText(std::ifstream& fin, std::ofstream& fout, std::string& mes)
{
    uint8_t tempBitSet = 0;
    char tempChar = 0;
    std::string::iterator iterOnChar = mes.begin();
    std::string::iterator iterOnEndMes = mes.end();

    while (fin.peek() != EOF) {
        fin.read(reinterpret_cast<char*>(&tempBitSet), sizeof(uint8_t));
        if(iterOnChar != iterOnEndMes) {
            tempChar = *iterOnChar;
            for (size_t i = 0; i < 8; ++i) {
                tempBitSet &= 0b11111110;
                tempBitSet |= (tempChar >> (7 - i)) & 0b00000001;
                fout.write(reinterpret_cast<char*>(&tempBitSet), sizeof(uint8_t));
                fin.read(reinterpret_cast<char*>(&tempBitSet), sizeof(uint8_t));
            }
        }
        else {
            fout.write(reinterpret_cast<char*>(&tempBitSet), sizeof(uint8_t));
        }
    }
}

#include "funcs.hpp"


template<char del>
void writeToBin(std::ofstream& fout, const TV<del>& source)
{   
    size_t tempSize = source.getFirm().size() * sizeof(char);

    fout.write((char*)(&tempSize), sizeof(size_t));
    fout.write(source.getFirm().c_str(), tempSize);
    tempSize = source.getSize();
    fout.write((char*)(&tempSize), sizeof(size_t));
    tempSize = source.getMarcket().size() * sizeof(char);
    fout.write((char*)(&tempSize), sizeof(size_t));
    fout.write(source.getMarcket().c_str(), tempSize);
    tempSize = sizeof(source.getPrice());
    fout.write((char*)(&tempSize), sizeof(size_t));
}

template<char del>
void readFromBin(std::ifstream& fin, TV<del>& source)
{
    size_t tempSize;
    std::string firmTitle;
    size_t size;
    std::string marcket;
    size_t price;

    fin.read((char*)(&tempSize), sizeof(size_t));
    


    fin.read((char*)(&firmTitle), tempSize);
    fin.read((char*)(&size), sizeof(size_t));
    fin.read((char*)(&tempSize), sizeof(size_t));
    fin.read((char*)(&marcket), tempSize);
    fin.read((char*)(&price), sizeof(size_t));

    source = TV<del>(firmTitle, size, marcket, price);
}

#include <iostream>
#include <fstream>
#include "funcs.hpp"
#include <vector>


int main(){
    std::string path("INPUT.txt");
    std::vector<std::pair<double, double>> persons = getVectorWithTime(path);
    for (size_t i = 0; i < persons.size(); ++i){
        std::cout << persons[i].first << "--" << persons[i].second << std::endl;
    }
    return 0;
}
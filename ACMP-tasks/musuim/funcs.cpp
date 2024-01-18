#include <fstream>
#include <vector>
#include <regex>
#include <iostream>

size_t getNumberOfVisier(std::string path)
{
    std::ifstream file(path);
    size_t number;
    file >> number;
    file.close();
    return number;
}

std::vector<std::pair<double, double>> getVectorWithTime(std::string path)
{
    std::string timeForOnePerson;
    std::ifstream file(path);
    std::regex delimSpace("\\W*");
    std::getline(file, timeForOnePerson);
    std::pair<double, double> person;
    std::vector<std::pair<double, double>> persons;
    while (!getline(file, timeForOnePerson)) {
        timeForOnePerson.replace(timeForOnePerson.begin(), timeForOnePerson.end(), ':', '.');
        std::sregex_token_iterator time(timeForOnePerson.begin(), timeForOnePerson.end(), delimSpace, -1);
        person.first = std::stod(*time++);
        person.second = std::stod(*time);
        std::cout << person.first << "--" << person.second << std::endl;
        persons.push_back(person);
    }
    return persons;
}

size_t countOfMaxPersons(std::vector<std::pair<double, double>> arr) 
{
    size_t maxNumber = 0;
    size_t tempMaxNumber = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        tempMaxNumber = 0;
        for (size_t j = 0; j < arr.size(); ++j) {
            if ( i != j && (arr[i].first <= arr[j].first && arr[i].second >= arr[j].first || // j отрезок входит в i началом
                arr[i].first <= arr[j].second && arr[i].second >= arr[j].second || // j отрезок входит в i концом
                arr[j].first <= arr[i].first && arr[j].second >= arr[i].first || // i отрезок входит в j началом
                arr[j].first <= arr[i].second && arr[j].second >= arr[j].second) // i отрезок входит в j концом 
            ) {
                ++tempMaxNumber;
            }
        }
        if (tempMaxNumber > maxNumber) {
            maxNumber = tempMaxNumber;
        }
    }
    return maxNumber;
}

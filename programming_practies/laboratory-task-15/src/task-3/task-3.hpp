#ifndef TASK_3
#define TASK_3
#include<iostream>
#include<fstream>
#include<vector>
#include<filesystem>
#include<format>
#include<regex>
#include<algorithm>


void checkFile(std::ifstream&, std::string);
void checkPath(std::string);
void readFromFile(std::ifstream&, std::vector<std::string>&);
void printVector(std::vector<std::string>&);
void printVectorWithChar(std::vector<std::string>&, char);
void thirdTask();


#endif // TASK_3
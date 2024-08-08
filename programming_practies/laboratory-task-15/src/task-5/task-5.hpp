#ifndef TASK_5
#define TASK_5
#include<iostream>
#include<vector>
#include<filesystem>
#include<algorithm>
#include<format>
#include<fstream>
#include<regex>
#include"src/Student/Student.hpp"
#include"src/task-3/task-3.hpp"


void checkFile(std::ifstream&, std::string);
void checkPath(std::string);
void readFile(std::vector<Student>&, std::ifstream&);
void writeToFile(const std::vector<Student>&, std::ofstream&);
void fiveTask(std::string&);

#endif // TASK_5
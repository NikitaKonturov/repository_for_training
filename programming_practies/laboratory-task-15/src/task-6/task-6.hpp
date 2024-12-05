#ifndef TASK_6
#define TASK_6
#include<iostream>
#include<vector>
#include<filesystem>
#include<algorithm>
#include<format>
#include<fstream>
#include<iterator>
#include"src/Train/Train.hpp"
#include"src/task-3/task-3.hpp"

void checkFile(std::ifstream&, std::string);
void checkPath(std::string);
void readFile(std::vector<Train>&, std::ifstream&);
void sixTask(std::string&);

#endif // TASK_6
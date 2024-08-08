#ifndef FUNCS_HPP
#define FUNCS_HPP
#include<filesystem>
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<format>
#include<cmath>
#include<regex>
#include<map>

void CheckInputPath(const std::filesystem::path& path_to_filesysteam_object);
void CheckFile(std::wifstream& wfin);
std::wstring ReadFile(std::wifstream& wfin);

std::wstring getNewSequence(std::wstring text, size_t offset, size_t start = 0);
std::wstring shiftTextAlfabet(std::wstring text, int64_t shift);
size_t checkShiftToKeyChar(std::wstring firstText, std::wstring secondText);
std::vector<size_t> getAlfabetShiftsForKey(std::wstring text, size_t keyLenght);
std::map<wchar_t, size_t> getFreqText(std::wstring text);
double getMatchIndex(std::wstring text);
double getMutualIndexCoincidence(std::wstring firstText, std::wstring secondText);
void getKeyLenght(std::wstring text);
void generateKey(std::vector<size_t> shiftsAlfabetKey);


std::wstring encryption(std::wstring openText, std::wstring key);
std::wstring dencryption(std::wstring cipherText, std::wstring key);



#endif //FUNCS_HPP

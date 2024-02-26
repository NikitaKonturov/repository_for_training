#include "pch.h"
#include <string>
#include <cstring>
#define _CRT_SECURE_NO_WARNINGS
#include "..\Laba11\func.cpp"
#include "..\Laba11\funcs.hpp"
TEST(testIsDigit, goodTest)
{
	std::string word = "32";
	EXPECT_TRUE(isDigit(word));
	word = "-89";
	EXPECT_TRUE(isDigit(word));
	word = "0";
	EXPECT_TRUE(isDigit(word));
}

TEST(testIsDigit, badTest)
{
	std::string word = "+56";
	EXPECT_FALSE(isDigit(word));
	word = "sfraf";
	EXPECT_FALSE(isDigit(word));
	word = "";
	EXPECT_FALSE(isDigit(word));
}

TEST(testFillingArr, goodTest)
{
	std::string text, delims = " ,.?!\\||/*&.,$#^%;:'\"@()";
	text = "gagr 433 gweg 34 gw";
	int32_t arr[5];
	fillingArr(arr, text, delims);
	EXPECT_EQ(arr[0], 433);
}

TEST(testFillingArr, badTest)
{
	std::string text, delims = "";
	text = "";
	int32_t arr[5];
	EXPECT_THROW(fillingArr(arr, text, delims), std::out_of_range);
}

TEST(testUniQuickSort, goodTest)
{
	std::string* arr = new std::string[4];
	arr[0] = "Bimbim";
	arr[1] = "Bambam";
	arr[2] = "Aaaa";
	arr[3] = "Cbbb";
	size_t begin = 0;
	size_t end = 3;
	universalQsort(arr, 0, 3, compairStrings);
	EXPECT_STREQ(arr[0].c_str(), "Aaaa");
	EXPECT_STREQ(arr[1].c_str(), "Bambam");
	EXPECT_STREQ(arr[2].c_str(), "Bimbim");
	EXPECT_STREQ(arr[3].c_str(), "Cbbb");
	delete[] arr;
}

TEST(testUniQuickSort, badTest)
{
	std::string* arr = new std::string[0];
	EXPECT_ANY_THROW(universalQsort(arr, 0, 3, compairStrings));
	delete[] arr;
}

TEST(testCaseExem, testCheckBadFile)
{
	std::ifstream fin("FEdf.faewfwe");
	EXPECT_THROW(checkFile(fin), std::invalid_argument) << "Check file on found";

	fin.open("C:\\Development\\Progects_second\\exemUnit\\exemUnit\\testFile.txt");
	EXPECT_THROW(checkFile(fin), std::runtime_error) << "Check file on empty";

	std::ifstream unopenFile;
	EXPECT_ANY_THROW(checkFile(unopenFile)) << "Check file on bad";
}

TEST(testCaseExem, testCheckGoodFile)
{
	std::ifstream fin("C:\\Development\\Progects_second\\exemUnit\\exemUnit\\Numbers.txt");
	EXPECT_TRUE(checkFile(fin));
}

TEST(testCompairStrings, goodTest)
{
	std::string wordFirst = "Aaaaa";
	std::string wordSecond = "Bbbbb";
	EXPECT_PRED2(compairStrings, wordFirst, wordSecond);
	wordFirst = "";
	EXPECT_PRED2(compairStrings, wordFirst, wordSecond);
	wordSecond = "";
	EXPECT_FALSE(compairStrings(wordFirst, wordSecond));
	wordFirst = "fsggs";
	EXPECT_FALSE(compairStrings(wordFirst, wordSecond));
}

TEST(testCompairStrings, badTest)
{
	std::string wordFirst = "";
	std::string wordSecond = "";
	EXPECT_FALSE(compairStrings(wordFirst, wordSecond));
}

TEST(testCompairStructToUpper, goodTest)
{
	Employee firstEmp;
	firstEmp.surename = "Aaaaa";
	Employee secondEmp;
	secondEmp.surename = "Bbbbb";
	EXPECT_TRUE(compForStructToUpper(firstEmp, secondEmp));
	firstEmp.surename = "aaaaaa";
	EXPECT_TRUE(compForStructToUpper(firstEmp, secondEmp));
}

TEST(testCompairStructToUpper, badTest)
{
	Employee firstEmp;
	firstEmp.surename = "Aaaaa";
	Employee secondEmp;
	secondEmp.surename = "";
	EXPECT_FALSE(compForStructToUpper(firstEmp, secondEmp));
	firstEmp.surename = "";
	EXPECT_FALSE(compForStructToUpper(firstEmp, secondEmp));
}

TEST(testCompairStructToLower, godTest)
{
	Employee firstEmp;
	firstEmp.surename = "Aaaaa";
	Employee secondEmp;
	secondEmp.surename = "Bbbbb";
	EXPECT_TRUE(compForStructToLower(secondEmp, firstEmp));
	firstEmp.surename = "aaaaaa";
	EXPECT_TRUE(compForStructToLower(secondEmp, firstEmp));
}

TEST(testCompairStructToLower, badTest)
{
	Employee firstEmp;
	firstEmp.surename = "Aaaaa";
	Employee secondEmp;
	secondEmp.surename = "";
	EXPECT_FALSE(compForStructToLower(secondEmp, firstEmp));
	firstEmp.surename = "";
	EXPECT_FALSE(compForStructToLower(secondEmp, firstEmp));
}

TEST(testPrintArr, badTestPrint)
{
	Employee* arr = new Employee[5];
	EXPECT_THROW(printArr(arr, -5), std::out_of_range);
	EXPECT_THROW(printArr(arr, 0), std::out_of_range);
}

TEST(testToUpper, goodTest)
{
	std::string testWord = "aaa";
	EXPECT_STREQ(toUpper(testWord).c_str(), "AAA");
}

TEST(testToUpper, badTest)
{
	std::string testWord = "aaa";
	EXPECT_STRNE(toUpper(testWord).c_str(), "aaa");
}

TEST(testGetMainText, goodTest)
{
	std::string path = "C:\\Development\\Progects_second\\exemUnit\\exemUnit\\testFileForGetMainText.txt";
	std::string testText = "first line second line three line";
	EXPECT_NO_THROW(getMainText(path));
	EXPECT_STREQ(getMainText(path).c_str(), testText.c_str());
}


TEST(testGetMainText, badTest)
{
	std::string path = "";
	EXPECT_ANY_THROW(getMainText(path));
}

TEST(testGetDelimiters, goodTest)
{
	std::string path = "C:\\Development\\Progects_second\\exemUnit\\exemUnit\\testFileForGetMainText.txt";
	std::string testText = "Hellow world";
	EXPECT_NO_THROW(getDelimiters(path));
	EXPECT_STREQ(getDelimiters(path).c_str(), testText.c_str());
}

TEST(testGetDelimiters, badTest)
{
	std::string path = "";
	EXPECT_ANY_THROW(getDelimiters(path));
}

TEST(testCopySortArrays, goodTest)
{
	int32_t testArray[5] = { 4, 51, 1, 5, 4 };
	int32_t testSortArray[5] = { 4, 4, 51, 1, 5 };
	int32_t outPutArray[5];
	copySortArrays(testArray, outPutArray, 5);
	for (size_t i = 0; i < 5; ++i) {
		EXPECT_EQ(outPutArray[i], testSortArray[i]);
	}
}

TEST(testCopySortArrays, badTest)
{
	int32_t testArray[5] = { 4, 51, 1, 5, 4 };
	int32_t outPutArray[5];
	EXPECT_THROW(copySortArrays(testArray, outPutArray, 0), std::out_of_range);
}

TEST(testGetSizeForArrSurenames, goodTest)
{
	std::string text = "Afafef Afewfaweaf Aefaeawe Fewff";
	std::string delim = " ,./?!";
	EXPECT_EQ(getSizeForArrSurenames(text, delim), 4);
}

TEST(testGetSizeForArrSurenames, badTest)
{
	std::string text = "";
	std::string delim = "";
	EXPECT_THROW(getSizeForArrSurenames(text, delim), std::invalid_argument);
}

TEST(testGetSizeForArrNumbers, goodTest)
{
	std::string text = "     324 jnjk, 343 nn,k 3434jn      ";
	std::string delim = " ";
	EXPECT_EQ(getSizeForArrNumbers(text, delim), 2);
}

TEST(testGetSizeForArrNumbers, badTest)
{
	std::string text = "";
	std::string delim = "";
	EXPECT_THROW(getSizeForArrNumbers(text, delim), std::invalid_argument);
}

TEST(testFillingArrOfStruct, goodTest)
{
	std::string arrOfSurenames[3] = { "Vadim", "Maxim", "Vlad" };
	Employee arrOfStruct[3];
	int32_t arrOfChildren[3] = { 1, 4, 5 };
	fillingArrOfStruct(arrOfStruct, arrOfChildren, arrOfSurenames, 3, 3);
	for (size_t i = 0; i < 3; ++i) {
		EXPECT_EQ(arrOfStruct[i].children, arrOfChildren[i]);
		EXPECT_STREQ(arrOfStruct[i].surename.c_str(), arrOfSurenames[i].c_str());
	}
}

TEST(testFillingArrOfStruct, badTest)
{
	std::string arrOfSurenames[3] = { "Vadim", "Maxim", "Vlad" };
	Employee arrOfStruct[3];
	int32_t arrOfChildren[3] = { 1, 4, 5 };
	EXPECT_THROW(fillingArrOfStruct(arrOfStruct, arrOfChildren, arrOfSurenames, 0, -56), std::invalid_argument);
}

TEST(testWriteArrOfStruct, goodTest)
{
	std::string path = "C:\\Development\\Progects_second\\exemUnit\\exemUnit\\testFileForWriteOfStruct.txt";
	Employee arr[3];
	arr[0].surename = "Vadim";
	arr[0].children = 1;
	arr[1].surename = "Maxim";
	arr[1].children = 4;
	arr[2].surename = "Vlad";
	arr[2].children = 5;
	writeArrOfStruct(path, arr, 3);
	std::ifstream fin(path);
	std::string line, textWord;
	std::regex delim("\\s+");
	size_t i = 0;
	while (std::getline(fin, line)) {
		std::sregex_token_iterator word(line.begin(), line.end(), delim, -1);
		textWord = *word++;
		EXPECT_STREQ(textWord.c_str(), arr[i].surename.c_str());
		textWord = *word;
		EXPECT_EQ(std::stoi(textWord), arr[i].children);
		++i;
	}
}

TEST(testWriteArrOfStruct, badTest)
{
	std::string path = "C:\\Development\\Progects_second\\exemUnit\\exemUnit\\testFileForWriteOfStruct.txt";
	Employee arr[3];
	EXPECT_THROW(writeArrOfStruct(path, arr, -5), std::invalid_argument);
}

TEST(testCompForStruct, testToLower)
{
	Employee first, second;
	first.surename = "Aaaa";
	second.surename = "Bbbb";
	EXPECT_TRUE(compForStructToLower(second, first));
	EXPECT_FALSE(compForStructToLower(first, second));
}

TEST(testCompForStruct, testToUpper)
{
	Employee first, second;
	first.surename = "Aaaa";
	second.surename = "Bbbb";
	EXPECT_FALSE(compForStructToUpper(second, first));
	EXPECT_TRUE(compForStructToUpper(first, second));
}

TEST(testWriteArrOfStructToBin, goodTest)
{
	std::string path = "testFileForBin.bin";
	Employee arr[3];
	arr[0].surename = "Vadim";
	arr[0].children = 1;
	arr[1].surename = "Maxim";
	arr[1].children = 4;
	arr[2].surename = "Vlad";
	arr[2].children = 5;
	EXPECT_NO_THROW(writeArrOfStructToBin(path, arr, 3));
}

TEST(testWriteArrOfStructToBin, badTest)
{
	std::string path = "testFileForBin.bin";
	Employee arr[3];
	EXPECT_THROW(writeArrOfStructToBin(path, arr, -8), std::invalid_argument);
}


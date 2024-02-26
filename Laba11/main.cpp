#include <cstring>
#include <algorithm>
#include "funcs.hpp"


void delArr(int32_t*& arr)
{
	delete[] arr;
}

void delArr(Employee*& arr) 
{
	delete[] arr;
}



void delArr(std::string* &arr)
{
	delete[] arr;
}

int main()
{
	try {
		std::string pathToSurenames = "Strings.txt";
		std::string pathToNumbers = "Numbers.txt";
		std::string pathToOutInTxt = "result.txt";
		std::string pathToOutInBin = "result.bat";

		std::string delimsToSurenames = getDelimiters(pathToSurenames);
		std::string textToSureNames = getMainText(pathToSurenames);
		size_t sizeArrToSurename = getSizeForArrSurenames(textToSureNames, delimsToSurenames);
		std::string* allSurenames = new std::string[sizeArrToSurename];

		if (sizeArrToSurename == 0) {
			std::cout << "Task not have solution...";
		}
		else {
			fillingArr(allSurenames, textToSureNames, delimsToSurenames);
			printArr(allSurenames, sizeArrToSurename);
			qsortString(allSurenames, 0, sizeArrToSurename - 1);
			printArr(allSurenames, sizeArrToSurename);

			std::string delimToNumber = getDelimiters(pathToNumbers);
			std::string textToNumbers = getMainText(pathToNumbers);
			size_t sizeArrToNumbers = getSizeForArrNumbers(textToNumbers, delimToNumber);
			int32_t* allNumbers = new int32_t[sizeArrToNumbers];
			int32_t* allSortNumbers = new int32_t[sizeArrToNumbers];

			if (sizeArrToNumbers == 0) {
				std::cout << "Task not have solution...";
			}
			else {
				fillingArr(allNumbers, textToNumbers, delimToNumber);
				printArr(allNumbers, sizeArrToNumbers);
				copySortArrays(allNumbers, allSortNumbers, sizeArrToNumbers);
				printArr(allSortNumbers, sizeArrToNumbers);
			}

			Employee* employees = new Employee[sizeArrToSurename];
			fillingArrOfStruct(employees, allNumbers, allSurenames, sizeArrToSurename, sizeArrToNumbers);

			printArr(employees, sizeArrToSurename);
			menu(employees, sizeArrToSurename);
			printArr(employees, sizeArrToSurename);

			std::cout << "##########" << std::endl;

			printArr(employees, sizeArrToSurename);
			writeArrOfStruct(pathToOutInTxt, employees, sizeArrToSurename);

			writeArrOfStructToBin(pathToOutInBin, employees, sizeArrToSurename);
			std::ifstream fin(pathToOutInBin, std::ios::binary);
			
			Employee employeeLast, employeeFirst;
			size_t pointerToLast = getPoiterLast(fin, employeeLast, employeeFirst);
			fin.close();
			std::ofstream fout(pathToOutInBin, std::ios::binary | std::ios::app);
			fout.close();
			swapLinesInBinareFile(fout, pointerToLast, employeeLast, employeeFirst);

			delArr(employees);
			delArr(allSortNumbers);
			delArr(allNumbers);
			delArr(allSurenames);
		}
	}
	catch (std::exception& err) {
		std::cerr << err.what() << std::endl;
	}

	return 0;

}
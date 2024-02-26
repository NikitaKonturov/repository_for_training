
#include "funcs.hpp"


bool checkFile(std::ifstream& file)
{
	if (!file.good()) {
		throw std::invalid_argument("File not found...");
	}
	if (!file) {
		throw std::ios_base::failure("Fileis bad...");
	}
	if (file.peek() == EOF) {
		file.close();
		throw std::runtime_error("File is empti...");
	}
	return true;
}

std::string getMainText(std::string path)
{
	std::ifstream fin(path);
	std::string line, text;

	if (checkFile(fin)) {
		std::getline(fin, line);
		while (std::getline(fin, line)) {
			text.append(line);
			text.append(" ");
		}
		fin.close();
		text[text.size() - 1] = '\0';
		return text;
	}
}

void printArr(int32_t* arr, int32_t size)
{
	if (size <= 0) {
		throw std::out_of_range("Bad size...");
	}
	for (size_t i = 0; i < size; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

std::string toUpper(std::string word)
{
	for (size_t i = 0; i < word.size(); ++i) {
		word[i] = std::toupper(word[i]);
	}
	return word;
}

bool compForStructToUpper(Employee firstPerson, Employee secondPerson)
{
	if (toUpper(firstPerson.surename) == toUpper(secondPerson.surename)) {
		return firstPerson.surename < secondPerson.surename;
	}
	return toUpper(firstPerson.surename) < toUpper(secondPerson.surename);
}

bool isDigit(std::string word)
{
	size_t size = word.size();
	if (word[0] == '-' || isdigit(word[0])) {
		for (size_t i = 1; i < size; ++i) {
			if (!isdigit(word[i])) {
				return false;
			}
		}
		return true;
	}
	return false;
}

void fillingArr(int32_t* arr, std::string text, std::string delims)
{
	
	if (text.size() == 0 || delims.size() == 0) {
		throw std::out_of_range("Bad size of string...");
	}

	std::string word;
	size_t begin = 0;
	size_t end = 0;
	size_t i = 0;


	begin = text.find_first_not_of(delims, end);
	end = text.find_first_of(delims, begin);
	bool textHaveNumbers = false;
	while (begin < end) {
		word = text.substr(begin, (end - begin));
		if (isDigit(word)) {
			textHaveNumbers = true;
			arr[i++] = std::stoi(word);
		}
		begin = text.find_first_not_of(delims, end);
		end = text.find_first_of(delims, begin);
	}
}

template<typename T>
void universalQsort(T* arr, size_t left, size_t right, bool (*comp)(T, T))
{
	size_t begin = left;
	size_t end = right;
	size_t mid = (left + right) / 2;

	T pivot = arr[mid];
	while (end > begin) {
		while (comp(arr[begin], pivot)) {  // arr[begin] < arr[mid]
			++begin;
		}
		while (comp(pivot, arr[end])) { // arr[end] > arr[mid]
			--end;
		}
		if (begin < end) {
			std::swap(arr[end], arr[begin]);
			--end;
			++begin;
		}
	}
	if (end < right) {
		universalQsort(arr, right, end, comp);
	}
	if (begin > left) {
		universalQsort(arr, begin, left, comp);
	}

}

void copySortArrays(int32_t* mainArr, int32_t* sortArr, int32_t size)
{
	if (size <= 0) {
		throw std::out_of_range("Bad size...");
	}
	size_t j = 0;
	for (size_t i = 0; i < size; ++i)
	{
		if (mainArr[i] % 2 == 0) {
			sortArr[j++] = mainArr[i];
		}
	}
	for (size_t i = 0; i < size; ++i)
	{
		if (mainArr[i] % 2 != 0) {
			sortArr[j++] = mainArr[i];
		}
	}
}


size_t getSizeForArrNumbers(std::string text, std::string delimiters)
{
	std::string word;
	size_t begin = 0;
	size_t end = 0;
	size_t size = 0;
	if (text.size() == 0 || delimiters.size() == 0) {
		throw std::invalid_argument("Bad args...");
	}

	begin = text.find_first_not_of(delimiters, end);
	end = text.find_first_of(delimiters, begin);
	while (begin < end) {
		word = text.substr(begin, (end - begin));
		if (isDigit(word)) {
			++size;
		}
		begin = text.find_first_not_of(delimiters, end);
		end = text.find_first_of(delimiters, begin);
	}
	return size;
}

size_t getSizeForArrSurenames(std::string text, std::string delimiters)
{
	std::string word;
	size_t begin = 0;
	size_t end = 0;
	size_t size = 0;
	if (text.size() == 0 || delimiters.size() == 0) {
		throw std::invalid_argument("Bad args...");
	}

	begin = text.find_first_not_of(delimiters, end);
	end = text.find_first_of(delimiters, begin);
	while (begin < end) {
		word = text.substr(begin, (end - begin));
		if (isWord(word)) {
			++size;
		}
		begin = text.find_first_not_of(delimiters, end);
		end = text.find_first_of(delimiters, begin);
	}
	return size;
}

bool isWord(std::string word)
{
	size_t size = word.size();
	if (isupper(word[0])) {
		for (size_t i = 1; i < size; ++i) {
			if (!isalpha(word[i])) {
				return false;
			}
		}
		return true;
	}
	return false;
}

void printArr(std::string* arr, int32_t size)
{
	if (size <= 0) {
		throw std::out_of_range("Bad size...");
	}
	for (size_t i = 0; i < size; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void qsortString(std::string* arr, size_t left, size_t right)
{
	size_t begin = left;
	size_t end = right;
	size_t mid = (left + right) / 2;


	while (end > begin) {
		while (compairStrings(arr[begin], arr[mid])) {
			++begin;
		}
		while (compairStrings(arr[mid], arr[end])) {
			--end;
		}
		if (begin < end) {
			std::swap(arr[end], arr[begin]);
			--end;
			++begin;
		}
	}

	if (end < right) {
		qsortString(arr, right, end);
	}
	if (begin > left) {
		qsortString(arr, begin, left);
	}
}

size_t inputChildren(std::string messege)
{
	size_t count = 0;
	do {
		std::cout << "Please enter a count of children for -- " << messege << std::endl;
		std::cin >> count;
	} while (count > 9);
	return count;
}

void fillingArrOfStruct(Employee* arrOfSttuct, int32_t* arrOfChildren, std::string* arrOfSurenames,
	int64_t sizeOfSurenames, int64_t sizeOfChildren)
{
	if (sizeOfSurenames <= 0 || sizeOfChildren <= 0){
		throw std::invalid_argument("Bad size...");
	}
	bool isNumer;
	size_t j = 0;
	for (size_t i = 0; i < sizeOfSurenames; ++i)
	{
		isNumer = false;
		arrOfSttuct[i].surename = arrOfSurenames[i];
		for (; j < sizeOfChildren; ++j) {
			if (arrOfChildren[j] < 10 && arrOfChildren[j] >= 0) {
				isNumer = true;
				arrOfSttuct[i].children = arrOfChildren[j];
				++j;
				break;
			}
		}
		if (!isNumer) {
			arrOfSttuct[i].children = inputChildren(arrOfSttuct[i].surename);
		}
	}
}

void printArr(Employee* arr, int32_t size)
{
	if (size <= 0) {
		throw std::out_of_range("Bad size...");
	}
	for (size_t i = 0; i < size; ++i) {
		std::cout << arr[i].surename << ' ' << arr[i].children << std::endl;
	}
}

void menu(Employee* employees, size_t size)
{
	bool (*funckOfSort[2])(Employee firstPerson, Employee secondPerson) = { compForStructToLower, compForStructToUpper };
	size_t variant = 0;
	do {
		std::cout << "Please enter a method of sort: |0 - descending|1 - ascending|: ";
		std::cin >> variant;
	} while (variant > 2);
	switch (variant) {
	case 0:
		universalQsort(employees, 0, size - 1, funckOfSort[0]);
		break;
	case 1:
		universalQsort(employees, 0, size - 1, funckOfSort[1]);
		break;
	}
}


void swapLinesInBinareFile(std::ofstream& fout, size_t pointerToLast, struct Employee employeeLast, struct Employee employeeFirst)
{
	fout.seekp(0);
	fout.write(reinterpret_cast<char*>(&employeeLast), sizeof(employeeLast));
	fout.seekp(pointerToLast - sizeof(employeeLast));
	fout.write(reinterpret_cast<char*>(&employeeFirst), sizeof(employeeFirst));
}

size_t getPoiterLast(std::ifstream& fin, struct Employee& employeeLast, struct Employee& employeeFirst)
{
	size_t pointerToLast = 0;

	fin.read(reinterpret_cast<char*>(&employeeFirst), sizeof(Employee));
	while (fin.read(reinterpret_cast<char*>(&employeeLast), sizeof(Employee))) {
		pointerToLast = fin.tellg();
	}

	return pointerToLast;
}

void writeArrOfStructToBin(std::string path, Employee* arr, int64_t size)
{
	if (size <= 0) {
		throw std::invalid_argument("Bad size...");
	}
	std::ofstream fout(path, std::ios::binary);
	if (fout.is_open()) {
		for (size_t i = 0; i < size; ++i) {
			fout.write(reinterpret_cast<char*>(&arr[i]), sizeof(Employee));
		}
		std::cout << "\nBin file is save!!!";
		fout.close();
	}
	else {
		throw std::ios_base::failure("File was not opened...");
	}
}

void writeArrOfStruct(std::string path, Employee* arr, int64_t size)
{
	if (size <= 0) {
		throw std::invalid_argument("Bad size...");
	}
	std::ofstream fout(path);
	if (fout.is_open()) {
		for (size_t i = 0; i < size; ++i) {
			fout << arr[i].surename << " " << arr[i].children << std::endl;
		}
		std::cout << "File is save!!!";
		fout.close();
	}
}

bool compForStructToLower(Employee firstPerson, Employee secondPerson)
{
	if (toUpper(firstPerson.surename) == toUpper(secondPerson.surename)) {
		return firstPerson.surename > secondPerson.surename;
	}
	return toUpper(firstPerson.surename) > toUpper(secondPerson.surename);
}

bool compairStrings(std::string wordFirst, std::string wordSecond)
{
	wordFirst = toUpper(wordFirst);
	wordSecond = toUpper(wordSecond);
	for (size_t i = 0; i < wordFirst.size() && i < wordSecond.size(); ++i) {
		if (wordFirst[i] < wordSecond[i]) {
			return true;
		} 
		else if (wordFirst[i] > wordSecond[i]) {
			return false;
		}
	}
	return wordFirst.size() < wordSecond.size();
}

void fillingArr(std::string* arr, std::string text, std::string delims)
{
	std::string word;
	size_t begin = 0;
	size_t end = 0;
	size_t i = 0;

	begin = text.find_first_not_of(delims, end);
	end = text.find_first_of(delims, begin);
	while (begin < end) {
		word = text.substr(begin, (end - begin));
		if (isWord(word)) {
			arr[i++] = word;
		}
		begin = text.find_first_not_of(delims, end);
		end = text.find_first_of(delims, begin);
	}
}

std::string getDelimiters(std::string path)
{
	std::ifstream fin(path);
	std::string delimiters{};

	if (checkFile(fin)) {
		std::getline(fin, delimiters);
		if (delimiters.size() == 0) {
			throw std::exception("Delimiters must be not empty...");
		}
		fin.close();
		return delimiters;
	}
}
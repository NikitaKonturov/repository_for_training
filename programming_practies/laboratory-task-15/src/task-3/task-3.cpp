#include"task-3.hpp"


void checkPath(std::string path) {
    std::filesystem::path pathToChek(path);
    if(!std::filesystem::exists(pathToChek)) {
        throw std::invalid_argument(std::format("Filesystem object by path {} is not exists!", path));
    } 

    if(!std::filesystem::is_regular_file(pathToChek)) {
        throw std::invalid_argument(std::format("Filesystem object by path {} is not a regular file!", path));
    }

    if(!pathToChek.has_extension() || pathToChek.extension() != std::filesystem::path(".txt")) {
        throw std::invalid_argument(std::format("Filesystem object by path {} has invalid extension!", path));
    }
} 


void checkFile(std::ifstream& fin, std::string path)
{
    checkPath(path);
	if (!fin) {
		std::string mes = "File is bad... Path: ";
		mes.append(path); 
		throw std::ios_base::failure(mes);
	}
	if (fin.peek() == EOF) {
		std::string mes = "File is empti... Path: ";
		mes.append(path); 
		throw std::runtime_error(mes);
	}
}

void readFromFile(std::ifstream& fin, std::vector<std::string>& source) 
{
    std::string allText;
    std::string line;
    while (getline(fin, line)) {
        allText.append(line);
    }
    
    std::regex delims("\\W+");
    std::sregex_token_iterator word(allText.begin(), allText.end(), delims, -1);
    std::sregex_token_iterator end;
    while(word != end) {
        source.push_back(*word);
        ++word;
    }
}

void printVector(std::vector<std::string>& vect) 
{
    for(const auto& i : vect) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void printVectorWithChar(std::vector<std::string>& vect, char character)
{
    bool vectorHaveThisElements = false;
    
    for(const auto& i : vect) {
        if (i[0] == character) {
            std::cout << i << " ";
            vectorHaveThisElements = true;
        }
    }
    if (!vectorHaveThisElements) {
        std::cout << "В векторе не содержиться слов на эту букву";
    }
    std::cout << std::endl;
}

void thirdTask() 
{
/*==============================================================================================================================*/

    std::string path;
    std::cout << "Введите полный путь к фалу: ";
    std::cin >> path;
    std::cout << std::endl;
    
/*==============================================================================================================================*/

    std::ifstream fin(path);

    checkFile(fin, path);

    std::vector<std::string> vectorWithWords;
    readFromFile(fin, vectorWithWords);

/*==============================================================================================================================*/

    std::cout << "Страй ветор: ";
    printVector(vectorWithWords);

    std::sort(vectorWithWords.begin(), vectorWithWords.end(), [](std::string& first, std::string& second){return first == second;});

    std::cout << "Отсортированный ветор: ";
    printVector(vectorWithWords);

/*==============================================================================================================================*/

    char letter;
    std::cout << "Введите букву(с учётом регистра): ";
    std::cin >> letter;
    std::cout << std::endl;
    
    std::cout << "Слова в векторе начинающиеся с этой буквы: ";
    printVectorWithChar(vectorWithWords, letter);

/*==============================================================================================================================*/

    char letterForDelete;
    std::cout << "Введите букву(с учётом регистра): ";
    std::cin >> letterForDelete;
    std::cout << std::endl;

    std::cout << "Старый ветор: ";
    printVector(vectorWithWords);

    std::vector<std::string>::iterator last = std::remove_if(vectorWithWords.begin(), vectorWithWords.end(), [letterForDelete](std::string& word){return word[0] == letterForDelete;});
    vectorWithWords.erase(last, vectorWithWords.end());

    std::cout << "Вектор после удаления: ";
    printVector(vectorWithWords);
}

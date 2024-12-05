#include"task-2.hpp"


void printVector(const std::vector<int>& source)
{
    for(const int& i : source) {
        std::cout << i << " ";
    }

    std::cout << std::endl;
}

void secondTask() 
{
     std::vector<int> numbers;

/*==============================================================================================================================*/

    int sourceElement = 0;
    std::cout << "Введите вектор" << std::endl;
     std::cout << "Введите " << 0 << " элемент: ";
    std::cin >> sourceElement;
    std::cout << std::endl;
    for (size_t i = 1; !std::cin.fail(); ++i) {
        numbers.push_back(sourceElement);
        std::cout << "Введите " << i << " элемент: ";
        std::cin >> sourceElement;
        std::cout << std::endl;
    }

/*==============================================================================================================================*/

    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "Сумма эллеметов вектора: " << sum << std::endl;
    std::cin.clear();
    std::cin.ignore();

/*==============================================================================================================================*/

    std::cout << "Введите элемент количество которого в векторе вы хотите узнать: ";
    std::cin >> sourceElement;
    std::cout << std::endl;

    std::cout << "Количество чисел равных заданному: " << std::count(numbers.begin(), numbers.end(), sourceElement) << std::endl;

/*==============================================================================================================================*/

    std::cout << "Введите элемент меньше которого должны быть числа: ";
    std::cin >> sourceElement;
    std::cout << std::endl;

    std::cout << "Количество чисел меньше " << sourceElement << ": " << std::count_if(numbers.begin(), numbers.end(), [sourceElement](int elem){return elem < sourceElement;}) << std::endl;
   
/*==============================================================================================================================*/

    std::cout << "Старый вектор: ";
    printVector(numbers);
    std::replace(numbers.begin(), numbers.end(), 0, static_cast<int>(sum/numbers.size()));
    std::cout << "Новый вектор(с заменнёными нулями на среднее арифметическое): ";
    printVector(numbers);

/*==============================================================================================================================*/

    int beginIndex = 0;
    int endIndex = numbers.size() - 1;

    std::cout << "Ведите итревал вектора: " << std::endl;
    std::cin >> beginIndex >> endIndex;
    
    if(beginIndex > endIndex) {
        std::swap(beginIndex, endIndex);
    }

    std::cout << "Сумма элементов в заданном интеварле вектора: " << std::accumulate(std::find(numbers.begin(), numbers.end(), numbers.at(beginIndex)), std::find(numbers.begin(), numbers.end(), numbers.at(endIndex)), 0) << std::endl; 

/*==============================================================================================================================*/

    int difference = *(std::max_element(numbers.begin(), numbers.end())) - *(std::min_element(numbers.begin(), numbers.end()));
    std::cout << "Вектор до замены чётных чисел на их разность: " << std::endl;
    printVector(numbers);

    std::replace_if(numbers.begin(), numbers.end(), [](int value){return !static_cast<bool>(value & 0x1);}, difference);

    std::cout << "Вектор после замены чётных чисел на их разность: " << std::endl;
    printVector(numbers);

/*==============================================================================================================================*/
    
    std::sort(numbers.begin(), numbers.end());
    std::cout << "Отсортированый вектор до удаления всех равных по модулю элементов: " << std::endl;
    printVector(numbers);

    std::vector<int>::iterator last = std::unique(numbers.begin(), numbers.end(), [](int controlElement, int testElemnt){return std::abs(controlElement) == std::abs(testElemnt);});
    numbers.erase(last, numbers.end());
   
    std::cout << "Отсортированый вектор после удаления элементов равных по подулю: " << std::endl;
    printVector(numbers);   


}

#include <algorithm>
#include "../class/magicCharacter.hpp"


bool compare(Character* first, Character* second)
{
    return first->getName() < second->getName();
}

template<typename T>
void universalQsort(T** arr, size_t left, size_t right, bool (*comp)(T*, T*))
{
	size_t begin = left;
	size_t end = right;
	size_t mid = (left + right) / 2;

	T* pivot = arr[mid];
	while (end > begin) {
		while (comp(arr[begin], pivot)) {  // arr[begin] < arr[mid]
			++begin;
		}
		while (comp(pivot, arr[end])) { // arr[end] > arr[mid]
			--end;
		}
		if (begin < end) {
			T* temp = arr[begin];
            arr[begin] = arr[end];
            arr[end] = temp;
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


int main()
{
    size_t maximCasts[] = {4, 8, 36};
    size_t vladCasts[] = {8, 9, 10, 59, 64};

    Character* arr[] = {new Character("Maxim", Race::gnom, State::normal, true), new magicCharacter("Kostya", Race::elf, State::paralyzed, false, 100, 3, maximCasts), new Character("Vadim", Race::human, State::normal, true), new magicCharacter("Vlad", Race::gnom, State::normal, true, 80, 5, vladCasts)};

    magicCharacter* temp;
    size_t defaultCharacter = 0;
    size_t wizardCharecter = 0;

    universalQsort(arr, 0, 3, compare);


    for (size_t i = 0; i < 4; ++i) {
        if (dynamic_cast<magicCharacter*>(arr[i])) {
            std::cout << *dynamic_cast<magicCharacter*>(arr[i]) << std::endl;
            ++wizardCharecter;
        }
        else {
            std::cout << *arr[i];
            std::cout << "Mana: not have" << std::endl;
            ++defaultCharacter; 
        }
        std::cout << "#####################################" << std::endl;
    }
    
    std::cout << "Count default character: " << defaultCharacter << std::endl;
    std::cout << "Cout magic character: " << wizardCharecter << std::endl;

    size_t controlMana = 0;
    std::cout << "Enter a searching mana: ";
    std::cin >> controlMana;
    std::cout << std::endl;

    for (size_t i = 0; i < 4; ++i) {
        if (dynamic_cast<magicCharacter*>(arr[i]) && dynamic_cast<magicCharacter*>(arr[i])->getActualMana() < controlMana) {
            std::cout << *dynamic_cast<magicCharacter*>(arr[i]) << std::endl;
            std::cout << "#####################################" << std::endl;
        }
    }   



    return 0;
}

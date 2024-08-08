#include "../funcs/funcs.hpp"
#include <locale>

#include <iostream>
#include <string>

int main() {
    std::string alfabet = "абвгдежзийклмнопрстуфхцчшщъыьэюя";

    std::string text;
    std::cin >> text;

    std::cout.imbue(std::locale("ru_RU.UTF-8"));

    for (size_t i = 0; i < 32; ++i) {
        std::cout << "Key: " << i << " ";

        std::string openText = text;

        for (size_t j = 0; j < text.size(); ++j) {
            size_t pos = alfabet.find(text[j]);
            if (pos != std::string::npos) {
                openText[j] = alfabet[(pos + i) % 32];
            } else {
                openText[j] = text[j];  // Если символ не найден в алфавите, оставляем его как есть
            }
        }

        std::cout << openText << std::endl;
    }

    return 0;
}

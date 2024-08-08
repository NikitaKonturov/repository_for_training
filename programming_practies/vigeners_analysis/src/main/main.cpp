
#include "../funcs/funcs.hpp"
#include <cwctype>
#include <locale>
#include <string>

int main() {
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::wcin.imbue(std::locale("ru_RU.UTF-8"));
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    std::wstring text;
    std::wstring path;

    // Читаем первую строку
    std::wcout << L"Введите путь: ";
    std::getline(std::wcin, path);

    // Очистка буфера ввода
    //std::cin.ignore();
    //std::cin.clear();
    //std::wcin.clear();
    //std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');

    std::string narrow_path(path.begin(), path.end());

    CheckInputPath(narrow_path);

    std::wifstream fin(narrow_path);

    if (!fin.is_open()) {
        std::wcerr << L"Не удалось открыть файл по пути: " << path.c_str() << std::endl;
        return 1;
    }

    text = ReadFile(fin);

    fin.close();

    for (wchar_t& ch : text) {
        ch = std::towupper(ch);
    }

    std::wcout << L"Открытый текст: " << std::endl;
    std::wcout << text << std::endl;

    // Читаем вторую строку
    std::wstring key = L"";
    std::wcout << L"Введите ключ: ";
    std::getline(std::wcin, key);

    if (key.empty()) {
        std::wcerr << L"Ключ не был введен." << std::endl;
        return 1;
    }

    std::wcout << L"Введенный ключ: " << key << std::endl;


    std::wstring cipherText = encryption(text, key);

    size_t keyLenght = 0;

    getKeyLenght(cipherText);

    std::wcout << "Введите длинну ключа: ";
    std::wcin >> keyLenght;

    std::vector<size_t> shiftsForKey = getAlfabetShiftsForKey(cipherText, keyLenght);

    generateKey(shiftsForKey);

//    std::wofstream wfout(narrow_path, std::ios_base::app);


//    wfout << cipherText << std::endl;

  //  wfout.close();




    //std::wcout << L"Результат дешифрования: " << dencryption(cipherText, key) << std::endl;

    return 0;
}

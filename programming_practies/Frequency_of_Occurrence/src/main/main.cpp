
#include "../funcs/funcs.hpp"
#include <algorithm>
#include <locale>
#include <vector>
#include <map>


int main()
{
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::wcin.imbue(std::locale("ru_RU.UTF-8"));
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    std::wstring alfabet = L"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЫЭЮЯ"; 

    std::map<wchar_t, size_t> frequency;
    for (size_t i = 0; i < alfabet.size(); ++i) {
        frequency[alfabet[i]] = 0;
    }
    
    std::wstring text;

    //std::wcin >> text;

    std::getline(std::wcin, text);

    for(wchar_t ch : text) {
        if(alfabet.find(ch) != std::wstring::npos) {
            ++frequency[ch];
        }
    }

    std::multimap<double, wchar_t, std::greater<double>> sortedFreq;

    std::wstring equalFreq = L"ОЕАИНТСРВЛКМДПУЯЫЬГЗБЧЙХЖШЮЦЩЭФъ";

    for(auto simbol : frequency) {
        sortedFreq.emplace(static_cast<double>(simbol.second) / 32.0, simbol.first);
    }

    std::cout.imbue(std::locale("ru_RU.UTF-8"));



/*фшу-злу кнгюшвца шъ пцйацйпг, нгйтощгщсшэ дцб яеълае пцйпг. йц ояе ъгхщшуш: дюоаюгнш инц, шуш езшюгэкх кцщкоя щъ пцйацйпг*/

    std::wcout << equalFreq << std::endl;
    for(auto simbol : sortedFreq) {
        std::wcout << simbol.second;
    }
    std::wcout << std::endl;




    std::cout << "Hello world!" << std::endl;
    return 0;
}

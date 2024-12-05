#include "funcs.hpp"


void CheckInputPath(const std::filesystem::path& path_to_filesysteam_object)
{
    if(!std::filesystem::exists(path_to_filesysteam_object)) {
        throw std::invalid_argument(std::format("Filesystem object by path: {} is not exists!", std::filesystem::absolute(path_to_filesysteam_object).string()));
    }
    if(!std::filesystem::is_regular_file(path_to_filesysteam_object)) {
        throw std::invalid_argument(std::format("Filesystem object by path: {} is not a regular file!", std::filesystem::absolute(path_to_filesysteam_object).string()));
    }
    if(!path_to_filesysteam_object.has_extension() || path_to_filesysteam_object.extension() != std::filesystem::path(".txt")) {
        throw std::invalid_argument(std::format("Filesystem object by path {} has invalid extension!", std::filesystem::absolute(path_to_filesysteam_object).string()));
    }
}

void CheckFile(std::wifstream &wfin)
{
    if(!wfin) {
        throw std::runtime_error("File is bad...");
    }
    if(!wfin.is_open()) {
        throw std::runtime_error("File was not opened...");
    }
}

std::wstring ReadFile(std::wifstream &wfin)
{
    CheckFile(wfin); 

    std::locale::global(std::locale("ru_RU.UTF-8"));
    wfin.imbue(std::locale("ru_RU.UTF-8"));

    std::wstring text;
    std::wstring line;

    while(std::getline(wfin, line)) {
        text.append(line);
    }

    return text;
}

std::wstring getNewSequence(std::wstring text, size_t offset, size_t start)
{
    if(start >= text.size()) {
        throw std::invalid_argument("Start index must be less that text size...");
    }

    std::wstring newSequence = L"";
    for (size_t i = start; i < text.size(); i += offset) {
            newSequence.push_back(text[i]);
    }
    
    return newSequence;
}

std::wstring shiftTextAlfabet(std::wstring text, int64_t shift)
{
    for(auto& ch : text) {
        ch -= 1040;
        ch = (ch + shift) % 32;
        ch = (ch < 0 ? ch + 1072 : ch + 1040);
    }

    return text;
}

size_t checkShiftToKeyChar(std::wstring firstText, std::wstring secondText)
{
    size_t shift = 0;
    double MutualIndex = 10.0;
    double temp = 0.0;

    for (size_t i = 1; i < 32; ++i) {
        temp = getMutualIndexCoincidence(shiftTextAlfabet(firstText, i), secondText);
        if(std::abs(temp - 0.0553) < std::abs(MutualIndex - 0.0553)) {
            MutualIndex = temp;
            shift = i;
            std::wcout << L"x: " << shift << L" Mutual index: "<< MutualIndex << std::endl;
        }
    }

    return shift;
}

std::vector<size_t> getAlfabetShiftsForKey(std::wstring text, size_t keyLenght)
{
    std::wstring setWithFirstLeters = getNewSequence(text, keyLenght, 0);

    std::vector<size_t> shfitsToKeyChar;

    for (size_t i = 1; i < keyLenght; ++i)
    {
        std::wcout << L"Shifts key leter number: " << i << std::endl;
        std::wcout << L"###############################" << std::endl;
        shfitsToKeyChar.push_back(checkShiftToKeyChar(setWithFirstLeters, getNewSequence(text, keyLenght, i)));
        
        std::wcout << L"###############################" << std::endl;
    }

    return shfitsToKeyChar;
}

std::map<wchar_t, size_t> getFreqText(std::wstring text)
{
    std::wregex unnecessarySimbols (L"\\W+");
    std::wregex unnecessarySimbolsOnBegin(L"^\\W+");
    std::wregex unnecessarySimbolsOnEnd(L"\\W+$");

    text = std::regex_replace(text, unnecessarySimbolsOnBegin, L"");
    text = std::regex_replace(text, unnecessarySimbolsOnEnd, L"");
    text = std::regex_replace(text, unnecessarySimbols, L"");

    std::wstring alfabet = L"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЫЭЮЯ";

    std::map<wchar_t, size_t> freq;
    for(auto ch : alfabet) {
        freq[ch] = 0;
    }

    for(auto ch : text) {
        ++freq[ch];
    }

    return freq;
}

double getMatchIndex(std::wstring text)
{
    double matchIndex = 0.0;
    std::map<wchar_t, size_t> freq = getFreqText(text);

    for(const auto& simbolFreq : freq) {
        matchIndex += simbolFreq.second * (simbolFreq.second - 1);
    }

    matchIndex /= (text.size() * (text.size() - 1));

    return matchIndex;
}

double getMutualIndexCoincidence(std::wstring firstText, std::wstring secondText)
{
    double mutualIndedxCoincidence = 0.0;

    std::map<wchar_t, size_t> firstTextFreq = getFreqText(firstText);
    std::map<wchar_t, size_t> secondTextFreq = getFreqText(secondText);

    auto indexFirstFreq = firstTextFreq.begin();
    auto indexSecondFreq = secondTextFreq.begin();

    for (; indexFirstFreq != firstTextFreq.end(); ++indexFirstFreq, ++indexSecondFreq) {
        mutualIndedxCoincidence += (indexFirstFreq->second * indexSecondFreq->second);
    }
    
    mutualIndedxCoincidence /= (firstText.size() * secondText.size());

    return mutualIndedxCoincidence;
}

void getKeyLenght(std::wstring text)
{
    for (size_t i = 2; i < text.size() * 0.1; ++i) { 
        std::wcout << "Key lenght: " << i << " match index:  " << getMatchIndex(getNewSequence(text, i, 0)) << std::endl;    
    }

    return;
}

void generateKey(std::vector<size_t> shiftsAlfabetKey)
{
    size_t keySize = shiftsAlfabetKey.size();

    std::wstring key(keySize + 1 , L'A');

    for (size_t i = 0; i < 32; ++i) {
        key[0] = 1040 + i;
        for (size_t i = 1; i < keySize + 1; ++i) {
            key[i] = 1040 + (((key[0] - 1040) + shiftsAlfabetKey[i - 1]) % 32);
        }


        std::wcout << L"Key: " << key << std::endl;
    }
}

std::wstring encryption(std::wstring openText, std::wstring key)
{   
    std::wregex unnecessarySimbols (L"\\W+");
    std::wregex unnecessarySimbolsOnBegin(L"^\\W+");
    std::wregex unnecessarySimbolsOnEnd(L"\\W+$");

    key = std::regex_replace(key, unnecessarySimbolsOnBegin, L"");
    key = std::regex_replace(key, unnecessarySimbolsOnEnd, L"");
    key = std::regex_replace(key, unnecessarySimbols, L"");
    
    openText = std::regex_replace(openText, unnecessarySimbolsOnBegin, L"");
    openText = std::regex_replace(openText, unnecessarySimbolsOnEnd, L"");
    openText = std::regex_replace(openText, unnecessarySimbols, L"");
    

    if(key.size() <= 1) {
        std::invalid_argument("Key must have size more that 1...");
    }

    std::wstring cipherText = openText;

    for (size_t i = 0; i < openText.size(); ++i) {
        uint16_t tempCh = (static_cast<uint16_t>(openText[i]) + static_cast<uint16_t>(key[i % key.size()]) - 2080) % 32;

        cipherText[i] = static_cast<wchar_t>(tempCh + 1040); 
    }
    
    return cipherText;
}

std::wstring dencryption(std::wstring cipherText, std::wstring key)
{
    if(key.size() <= 1) {
        std::invalid_argument("Key must have size more that 1...");
    }

    std::wstring openText = cipherText;

    for (size_t i = 0; i < openText.size(); ++i) {
        
        int16_t tempCh = (static_cast<int16_t>(cipherText[i]) - static_cast<int16_t>(key[i % key.size()]));

        openText[i] = static_cast<wchar_t>(tempCh < 0 ? tempCh + 1072 : tempCh + 1040); 
    }

    return openText;
}

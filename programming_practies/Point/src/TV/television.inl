#include "television.hpp"


template<char sDelim>
TV<sDelim>::TV(std::string sFirmTitle, double sSize, std::string sMarcket, size_t sPrice) : firmTitle(sFirmTitle), size(sSize), marcketTitle(sMarcket), price(sPrice)
{}

template<char sDelim>
TV<sDelim>::TV(const TV& source) : firmTitle(source.firmTitle), size(source.size), marcketTitle(source.marcketTitle), price(source.price)
{}

template<char sDelim>
TV<sDelim>& TV<sDelim>::operator=(const TV& source)
{
    if (this == &source) {
        throw std::invalid_argument("Self-education...");
    }

    this->firmTitle = source.marcketTitle;
    this->size = source.size;
    this->marcketTitle = source.marcketTitle;
    this->price = source.price;

    return *this;
}

template<char sDelim>
std::ostream& operator<<(std::ostream& out, const TV<sDelim>& source)
{
    out << "Firm title: " << source.firmTitle << std::endl;
    out << "Size: " << source.size << std::endl;
    out << "Marcket: " << source.marcketTitle << std::endl;
    out << "Price: " << source.price << std::endl;

    return out;
}

template<char sDelim>
std::istream& operator>>(std::istream& in, TV<sDelim>& source)
{
    std::string line = "";

    std::getline(in, line);
    if (line.empty()) {
        in.setstate(std::ios_base::failbit);
        return in;
    }
    std::string sDelimiter;
    sDelimiter.push_back(sDelim);
    std::regex delim(sDelimiter);
    std::regex space("\\s+");
    std::regex spaceBoard("^\\s+|\\s+$");

    line = std::regex_replace(line, space, " ");
    line = std::regex_replace(line, spaceBoard, "");

    std::sregex_token_iterator word(line.begin(), line.end(), delim, -1);
    std::sregex_token_iterator end;

    if (word == end) {
        in.setstate(std::ios_base::failbit);
        return in;    
    }

    source.firmTitle = *word;
    ++word;

    if (word == end) {
        in.setstate(std::ios_base::failbit);
        return in;    
    }

    source.size = std::stod(*word);
    ++word;
    
    if (word == end) {
        in.setstate(std::ios_base::failbit);
        return in;    
    }

    source.marcketTitle = *word;
    ++word;
    
    if (word == end) {
        in.setstate(std::ios_base::failbit);
        return in;    
    }

    source.price = std::stoi(*word);
    
    return in;
}

template<char sDelim>
std::string TV<sDelim>::getFirm() const
{
    return this->firmTitle;
}

template<char sDelim>
size_t TV<sDelim>::getSize() const
{
    return this->size;
}

template<char sDelim>
std::string TV<sDelim>::getMarcket() const
{
    return this->marcketTitle;
}

template<char sDelim>
size_t TV<sDelim>::getPrice() const
{
    return this->price;
}

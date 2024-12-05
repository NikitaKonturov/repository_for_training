#include"Student.hpp"


Student::Student(std::string sName, int64_t sCource, int64_t sGroup) : name(sName)
{
    if(sCource <= 0) {
        throw std::invalid_argument("Cource must be natural...");
    }
    if(sGroup <= 0) {
        throw std::invalid_argument("Group must be natural... ");
    }
    this->cource = sCource;
    this->group = sGroup;
}

std::ostream& operator<<(std::ostream& out, const Student& source)
{
    out << source.name << " " << source.group << " " << source.cource; 
    return out;
}
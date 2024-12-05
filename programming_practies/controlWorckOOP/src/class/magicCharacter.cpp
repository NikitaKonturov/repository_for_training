#include"magicCharacter.hpp"
#include<assert.h>


magicCharacter::magicCharacter(std::string sourceName, Race sourceRace, State sourceState, bool sourceAbility, size_t sourceMaxMana, uint8_t sourceCountMonths, size_t* sourceArr) :
                                Character(sourceName, sourceRace, sourceState, sourceAbility),
                                maxMana(sourceMaxMana),
                                actualMana(maxMana)
{
    
    assert(sourceCountMonths <= 12);
    countMonths = sourceCountMonths; 
    arrOfSessions = new size_t[countMonths];
    if(sourceArr == nullptr) {
        for (size_t i = 0; i < countMonths; ++i) {
            arrOfSessions[i] = 0;   
        }   
    }
    else {
        for (size_t i = 0; i < countMonths; ++i) {
            arrOfSessions[i] = sourceArr[i];   
        }
    }
}

magicCharacter::magicCharacter(const magicCharacter& source) :
                                Character(source),
                                maxMana(source.maxMana),
                                actualMana(source.actualMana)
{
    assert(source.countMonths <= 12);
    countMonths = source.countMonths;

    arrOfSessions = new size_t[countMonths];
    for (size_t i = 0; i < countMonths; ++i) {
        arrOfSessions[i] = source.arrOfSessions[i];
    }
}

size_t magicCharacter::getActualMana() const
{
    return actualMana;
}

void magicCharacter::setActualMana(size_t source)
{
    if (source > maxMana) {
        throw std::invalid_argument("Actual mana must be less or eqal...");
    }
    actualMana = source;
}

size_t magicCharacter::getMaxMana() const
{
    return maxMana;
}

void magicCharacter::setMaxMana(size_t source)
{
    maxMana = source;
}

magicCharacter& magicCharacter::operator=(const magicCharacter& source)
{
    name = source.name;
    race = source.race;
    state = source.state;
    moveAbility = source.moveAbility;
    maxMana = source.maxMana;
    actualMana = source.actualMana;
    countMonths = source.countMonths;

    delete[] arrOfSessions;

    arrOfSessions = new size_t[countMonths];
    for (size_t i = 0; i < countMonths; ++i)  {
        arrOfSessions[i] = source.arrOfSessions[i];
    }
    return *this;
}

size_t magicCharacter::getCountMonths() const
{
    return countMonths;
}

size_t& magicCharacter::operator[](size_t i)
{   
    if(i > countMonths) {
        throw std::out_of_range("Out of months...");
    }
    return arrOfSessions[i];
} 

void magicCharacter::setArrOfSessions(size_t* sourceArr, size_t sourceSize)
{
    if(sourceSize > 12) {
        throw std::logic_error("Size of array must be less or equal 12");
    }

    delete[] arrOfSessions;

    countMonths = sourceSize;
    arrOfSessions = new size_t[countMonths]; 
    for (size_t i = 0; i < countMonths; ++i) {
        arrOfSessions[i] = sourceArr[i];
    }
}

std::ostream& operator<<(std::ostream& out, const magicCharacter& source)
{
    source.print(out);
    out << "Mana capacity: " << source.maxMana << std::endl;
    out << "Mana: " << source.actualMana << std::endl;
    for (size_t i = 0; i < source.countMonths; ++i) {
        out << "In "<< i + 1 << " month have session: " << source.arrOfSessions[i] << std::endl; 
    }
    
    return out;
}

magicCharacter::~magicCharacter()
{
    delete[] arrOfSessions;
}

#ifndef MAGICCHARACTER_HPP
#define MAGICCHARACTER_HPP
#include"Character.hpp"
#include<stdint.h>

class magicCharacter final : public Character{
private:
    size_t maxMana;
    size_t actualMana;
    uint8_t countMonths;
    size_t* arrOfSessions;
public:
    magicCharacter(std::string = "No name", Race = Race::human, State = State::paralyzed, bool = true, size_t = 10, uint8_t = 1, size_t* = nullptr);
    magicCharacter(const magicCharacter&);
    
    size_t getActualMana() const;
    void setActualMana(size_t);

    size_t getCountMonths() const; 
    void setArrOfSessions(size_t*, size_t);

    size_t getMaxMana() const;
    void setMaxMana(size_t);

    virtual magicCharacter& operator=(const magicCharacter&);

    size_t& operator[](size_t); 

    friend std::ostream& operator<<(std::ostream&, const magicCharacter&);

    ~magicCharacter();
};


#endif // MAGICCHARACTER_HPP
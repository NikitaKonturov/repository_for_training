#include "Character.hpp"
#include<string.h>


size_t Character::countID = 0;

Character::Character(std::string sourceName, Race sourceRace, State sourceState, bool sourceAbility) : 
            name(sourceName),
            race(sourceRace),
            state(sourceState),
            moveAbility(sourceAbility),
            ID(++countID)
{}

Character::Character(const Character& origin) : 
            name(origin.name), 
            race(origin.race), 
            state(origin.state), 
            moveAbility(origin.moveAbility),
            ID(++countID)
{}

Race Character::getRace() const
{
    return race;
}

void Character::setRace(const Race& source)
{
    race = source;
}

State Character::getState() const
{
    return state;
}

void Character::setState(const State& source)
{
    state = source;
} 

std::string Character::getName() const
{
    return name;
}

void Character::setName(std::string source)
{
    name = source;
}

Character& Character::operator=(const Character& source)
{
    if(this != &source) {
        name = source.name;
        race = source.race;
        state = source.state;
        moveAbility = source.moveAbility;
    }
    return *this;
}

std::ostream& Character::print(std::ostream& out) const
{
    out << "ID: " <<  ID << std::endl;
    out << "Name: " << name << std::endl;
    out << "Race: ";
    switch (race)
    {
    case Race::human:
        out << "human "<< std::endl;
        break;
    case Race::elf:
        out << "elf " << std::endl;
        break;
    case Race::gnom:
        out << "gnom " << std::endl;
        break;
    }
    out << "State: ";
    switch (state)
    {
    case State::normal:
        out << "normal "<< std::endl;
        break;
    case State::dead:
        out << "dead " << std::endl;
        break;
    case State::paralyzed:
        out << "paralyzed " << std::endl;
        break;
    }
    out << "Ability to move: ";
    if (moveAbility){
        out << "true " << std::endl;
    }
    else {    
        out << "false " << std::endl;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Character& source)
{
    return source.print(out);
}

bool Character::operator==(const Character& source)
{
    return strcmp(this->name.c_str(), source.name.c_str());
}

size_t Character::getID()
{
    return ID;
}

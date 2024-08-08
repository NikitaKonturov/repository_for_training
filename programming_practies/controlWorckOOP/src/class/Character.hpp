
#ifndef CLASS_HPP
#define CLASS_HPP
#include<iostream>
#include<iostream>
#include<cstring>


enum class Race {
    human,
    gnom,
    elf,
};

enum class State {
    normal,
    paralyzed,
    dead,
};

class Character {
protected:
    static size_t countID; 
    const size_t ID;
    std::string name;
    Race race;
    State state;
    bool moveAbility;
    std::ostream& print(std::ostream&) const;
public:
    Character(std::string = "No name", Race = Race::human, State = State::paralyzed, bool = true);
    Character(const Character&);

    Race getRace() const;
    void setRace(const Race&);

    State getState() const;
    void setState(const State&);

    std::string getName() const;
    void setName(std::string);

    virtual Character& operator=(const Character&);

    bool operator==(const Character&);

    virtual ~Character() = default;

    friend std::ostream& operator<<(std::ostream&, const Character&);
    size_t getID();
};





#endif //CLASS_HPP

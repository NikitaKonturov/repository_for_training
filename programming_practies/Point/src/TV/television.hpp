#ifndef TV_HPP
#define TV_HPP
#include <iostream>
#include <regex>


template<char sDelim>
class TV 
{ 
private: 
    std::string firmTitle;
    size_t size;
    std::string marcketTitle;
    size_t price;
public:
    TV(std::string = "", double = 0.0, std::string = "", size_t = 0);
    TV(const TV&);
    ~TV() = default;

    TV& operator=(const TV&);

    std::string getFirm() const;
    size_t getSize() const;
    std::string getMarcket() const;
    size_t getPrice() const;


    template<char del>
    friend std::ostream& operator<<(std::ostream&, const TV<del>&);
    template<char del>
    friend std::istream& operator>>(std::istream&, TV<del>&);
};

#include"television.inl"

#endif // TV_HPP
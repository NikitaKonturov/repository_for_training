#ifndef STUDENT_HPP
#define STUDENT_HPP
#include<iostream>


class Student
{
public:
    std::string name;
    size_t cource;
    size_t group;

    Student(std::string, int64_t, int64_t);
    ~Student() = default;

    friend std::ostream& operator<<(std::ostream&, const Student&);
};



#endif // STUDENT_HPP
#ifndef MYSTRING_HPP
#define MYSTRING_HPP
#include <iostream>
#include <cstring>

class myString {
private:
    char* str;
    size_t size;
    size_t capacity;

public:
    myString();
    myString(int64_t);
    myString(const myString&);
    myString(myString&&);
    myString(const char*);
    ~myString();
    void push_back(char);
    void append(const myString&);
    void append(char*);
    void append(const char*);
    void insert(const char*, size_t);
    void insert(const myString&, size_t);
    myString substr(size_t, size_t) const;
    void replace(const myString&, size_t, size_t);
    void replace(const char*, size_t, size_t);
    void clear();
    size_t getSize() const;
    bool empty() const;

 
    char& operator[](int64_t);
    void operator=(const myString&);
    void operator=(const char*);
    myString operator+(const myString&) const;

    friend std::ostream& operator<<(std::ostream&, myString&);
    friend std::istream& operator>>(std::istream&, myString&);

};


#endif //MYSTRING_HPP
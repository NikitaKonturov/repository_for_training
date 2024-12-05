#include "myString.hpp"


myString::myString()
{
 size = 0;
 capacity = 0;
 str = new char[0];
}

myString::myString(int64_t sizeToString) 
{
    if (sizeToString <= 0) {
        throw std::invalid_argument("Bad size...");
    }
    capacity = sizeToString * 2;
    size = sizeToString;
    str = new char[capacity];
    str[size] = '/0';
}

myString::myString(const myString& source) 
{
 capacity = source.capacity;
 size = source.size;
 str = new char[capacity];
 for (size_t i = 0; i < size; ++i) {
  str[i] = source.str[i];
 }
 str[size] = '/0';
}

myString::myString(const char* source) 
{
    size_t sourceSize = std::strlen(source);
    size = sourceSize;
    capacity = size*2;
    str = new char[capacity];
    for (size_t i = 0; i < size; ++i) {
        str[i] = source[i];
    }
    str[size] = '/0';
}

myString::myString(myString &&source)
{
    size = source.size;
    capacity = source.capacity;
    source.str = nullptr;
}

myString::~myString()
{
    if(str != nullptr) {
        delete[] str;
    }
}

void myString::push_back(char item)
{
    if (size == capacity) {
        if(size == 0) {
            capacity = 1 * 2;
            str = new char[capacity];
            str[size++] = item;
            str[size] = '/0';
        } 
        else {
            char* tmp = new char[size * 2];
            for (size_t i = 0; i < size; ++i) {
                tmp[i] = str[i];
            }
            tmp[size++] = item;
            tmp[size] = '/0';
            capacity = size * 2;
            delete[] str;
            str = tmp;
        }
    }
    else {
        str[size++] = item;
        str[size] = '/0';
    }
}

void myString::append(const myString& source)
{
    if(capacity > (size + source.size)) {
        for (size_t i = 0, j = size; i < source.size; ++i, ++j) {
            str[j] = source.str[i];
        }
        size += source.size;
        str[size] = '/0'; 
    }
    else {
        char* tmp = new char[(size + source.size) * 2];
        size_t j = 0;
        for (size_t i = 0; i < size; ++i, ++j) {
            tmp[j] = str[i];
        }
        for (size_t i = 0; i < source.size; ++i, ++j) {
            tmp[j] = source.str[i];
        }
        size += source.size;
        delete[] str;
        str = tmp;
        str[size] = '/0';
    }
}

void myString::append(char* source)

{
    size_t sourceSize = std::strlen(source);
    if(capacity > (size + sourceSize)) {
        for (size_t i = 0, j = size; i < sourceSize; ++i) {
            str[j] = source[i];        
        }
        str[size] = '/0';
    } 
    else {
        char* tmp = new char[(size + sourceSize) * 2];
        size_t j = 0;
        for (size_t i = 0; i < size; ++i, ++j) {
            tmp[j] = str[i];
        }
        for (size_t i = 0; i < sourceSize; ++i, ++j) {
            tmp[j] = source[i];
        }
        delete[] str;
        size += sourceSize;
        str = tmp;
        str[size] = '/0';
    }
}

void myString::append(const char* source)
{
    size_t sourceSize = std::strlen(source);
    if(capacity < (size + sourceSize)) {
        for (size_t i = 0, j = size; i < sourceSize; ++i, ++j) {
            str[j] = source[i];
        }
        str[size] = '/0';
    }
    else {
        char* tmp = new char[(size + sourceSize) * 2];
        size_t j = 0;
        for (size_t i = 0; i < size; ++i, ++j) {
            tmp[j] = str[i];
        }
        for (size_t i = 0; i < sourceSize; ++i, ++j) {
            tmp[j] = source[i];
        }
        delete[] str;
        size += sourceSize;
        str = tmp;
        str[size] = '/0';
    }
}

void myString::insert(const char* source, size_t pos) 
{
    if (pos > size) {
        throw std::out_of_range("Bad position..."); 
    }
    size_t sourceSize = std::strlen(source);
    if(capacity > (size + sourceSize)) {
        char* tmp = new char[size - pos];
        for (size_t i = pos, j = 0; i < size; ++i, ++j) {
            tmp[j] = str[i];
        }
        for (size_t i = 0, j = pos; i < sourceSize; ++i, ++j) {
            str[j] = source[i];
        }
        for (size_t i = 0, j = pos + sourceSize; i < size - pos; ++i, ++j) {
            str[j] = tmp[i];
        }
        delete[] tmp;
        size += sourceSize;
        str[size] = '/0';
    } 
    else {
        char* result = new char[(size + sourceSize) * 2];
        size_t j = 0;
        for (size_t i = 0; i < pos; ++i, ++j) {
            result[j] = str[i];
        }
        for (size_t i = 0; i < sourceSize; ++i, ++j) {
            result[j] = source[i];
        }
        for (size_t i = pos; i < size; ++i, ++j) {
            result[j] = str[i];  
        }
        delete[] str;
        str = result;
        str[size] = '/0';
        delete[] result;
    }

}

void myString::insert(const myString& source, size_t pos)
{
    if(pos >= size) {
        throw std::out_of_range("Bad position...");
    }
    if (capacity > size + source.size) {
        char* tmp = new char[size - pos];
        for (size_t i = 0, j = pos; j < size; ++i, ++j) {
            tmp[i] = source.str[j];
        }
        for (size_t i = 0, j = pos; i < source.size; ++i, ++j) {
            str[j] = source.str[i];
        }
        for (size_t i = 0, j = pos + source.size; i < size - pos; ++i, ++j) {
            str[j] = tmp[i];
        }
        size += source.size;
        capacity = size * 2;
        delete[] tmp;
        str[size] = '/0'; 
    }
    else {
        char* tmp = new char[(size + source.size) * 2];
        for (size_t i = 0; i < pos; ++i) {
            tmp[i] = str[i];
        }
        for (size_t i = 0, j = pos; i < source.size; ++i) {
            tmp[j] = source.str[i];    
        }
        for (size_t i = pos, j = pos+source.size; i < size; ++i, ++j) {
            tmp[j] = str[i];
        }
        str = tmp;
        str[size] = '/0';
    }
}

myString myString::substr(size_t pos, size_t lenght) const
{
    if(pos + lenght > size) {
        throw std::out_of_range("Out of range...");
    }
    myString result(lenght); 
    for (size_t i = pos, j = 0; i < pos+lenght; ++i, ++j) {
        result.str[j] = str[i];
    }
    return result;
}

void myString::replace(const myString& source, size_t pos, size_t lenght)
{
    if(pos + lenght > size) {
        throw std::out_of_range("Out of range...");
    }
    if(capacity > (size + source.size - lenght)) {
        char* tmp = new char[size - pos - lenght];
        for (size_t i = 0, j = pos + lenght; j < size; ++i, ++j) {
            tmp[i] = source.str[j];
        }
        for (size_t i = 0, j = pos; i < source.size; ++i, ++j) {
            str[j] = source.str[i];
        }
        for (size_t i = 0, j = pos + source.size; i < size - pos - lenght; ++i, ++j) {
            str[j] = tmp[i];
        }
        size = size - lenght + source.size;
        delete[] tmp;
        str[size] = '/0';
    }
    else {
        char* tmp = new char[size - lenght + source.size];
        for (size_t i = 0; i < pos; ++i) {
            tmp[i] = str[i];
        }
        for (size_t i = pos, j = 0; j < source.size; i++) {
            tmp[i] = source.str[j];
        }
        for (size_t i = pos + lenght, j = source.size + pos; i < size; ++i, ++j) {
            tmp[j] = str[i]; 
        }
        size = size - lenght + source.size;
        capacity = size * 2;
        delete[] str;
        str = tmp;
        str[size] = '/0';
    }
}

void myString::replace(const char* source, size_t pos, size_t lenght)
{
    if(pos + lenght > size) {
        throw std::out_of_range("Out of range...");
    }
    size_t sourceSize = std::strlen(source);
    if(capacity > (size + sourceSize - lenght)) {
        char* tmp = new char[size - pos - lenght];
        for (size_t i = 0, j = pos + lenght; j < size; ++i, ++j) {
            tmp[i] = source[j];
        }
        for (size_t i = 0, j = pos; i < sourceSize; ++i, ++j) {
            str[j] = source[i];
        }
        for (size_t i = 0, j = pos + sourceSize; i < size - pos - lenght; ++i, ++j) {
            str[j] = tmp[i];
        }
        size = size - lenght + sourceSize;
        delete[] tmp;
        str[size] = '/0';
    }
    else {
        char* tmp = new char[size - lenght + sourceSize];
        for (size_t i = 0; i < pos; ++i) {
            tmp[i] = str[i];
        }
        for (size_t i = pos, j = 0; j < sourceSize; i++) {
            tmp[i] = source[j];
        }
        for (size_t i = pos + lenght, j = sourceSize + pos; i < size; ++i, ++j) {
            tmp[j] = str[i]; 
        }
        size = size - lenght + sourceSize;
        capacity = size * 2;
        delete[] str;
        str = tmp;
        str[size] = '/0';
    }
}

void myString::clear() 
{
    size = 0;
    capacity = 0;
    delete[] str;
}

size_t myString::getSize() const
{
 return size;
}

bool myString::empty() const
{
    return size == 0;
}

char& myString::operator[](int64_t iterator)
{
 if (iterator < 0) {
  throw std::out_of_range("Bad index...");
 }
 return str[iterator];
}

void myString::operator=(const myString& source)
{
    size = source.size;
    capacity = source.capacity;
    delete[] str;
    str = new char[capacity];
    for (size_t i = 0; i < size; ++i) {
        str[i] = source.str[i];
    }
    str[size] = '/0';
}

void myString::operator=(const char* source)
{
    size = std::strlen(source);
    capacity = size * 2;
    delete[] str;
    str = new char[capacity];
    for (size_t i = 0; i < size; ++i) {
        str[i] = source[i];
    }
    str[size] = '/0';
}

std::ostream& operator<<(std::ostream& out, myString& source)
{
    for (size_t i = 0; i < source.size; ++i) {
       out << source.str[i];
    }
    
    return out;
}

std::istream& operator>>(std::istream& in, myString& source)
{
    delete[] source.str;
    source.str = new char[0]; 
    source.size = 0;
    source.capacity = 0;
    char liter;
    while(in.get(liter) && liter != ' ') {
         source.push_back(liter);
    }
    return in;
}

myString myString::operator+(const myString& source) const
{
    myString result = *this;
    result.append(source);
    return result;
}

#ifndef FUNCS_HPP
#define FUNCS_HPP
#include<iostream>

class ComplexNumbers {
private:
    double rel;
    double img;
public:
    ComplexNumbers();
    ComplexNumbers(double, double);
    ComplexNumbers(const ComplexNumbers&);
    ~ComplexNumbers();
 
    void setRel(double);
    void setImg(double);

    double getRel() const;
    double getImg() const;

    void operator=(const ComplexNumbers&);
    void operator=(double);

    ComplexNumbers operator+(const ComplexNumbers&) const;
    ComplexNumbers operator+(double) const;
    ComplexNumbers operator-(const ComplexNumbers&) const;
    ComplexNumbers operator-(double) const;
 
    friend ComplexNumbers operator+(double, const ComplexNumbers&) ;
    friend ComplexNumbers operator-(double, const ComplexNumbers&) ;

    ComplexNumbers operator*(const ComplexNumbers&) const;
    ComplexNumbers operator*(double) const;

    friend ComplexNumbers operator*(double, const ComplexNumbers&);

    ComplexNumbers& operator+=(const ComplexNumbers&);
    ComplexNumbers& operator+=(double);

    ComplexNumbers& operator-=(const ComplexNumbers&);
    ComplexNumbers& operator-=(double);

    ComplexNumbers& operator++();
    ComplexNumbers operator++(int);

    ComplexNumbers& operator--();
    ComplexNumbers operator--(int);

    ComplexNumbers operator/(const ComplexNumbers&);
    ComplexNumbers operator/(double);
    


};

#endif //FUNCS_HPP

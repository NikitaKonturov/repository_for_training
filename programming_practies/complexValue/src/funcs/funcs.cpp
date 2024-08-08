
#include "funcs.hpp"


ComplexNumbers::ComplexNumbers(): rel(0), img(0) {} 

ComplexNumbers::ComplexNumbers(double relS, double imgS) : rel(relS), img(imgS){}

ComplexNumbers::ComplexNumbers(const ComplexNumbers& origin)
{
    this->rel = origin.rel;
    this->img = origin.img;
}

ComplexNumbers::~ComplexNumbers() = default;

void ComplexNumbers::setRel(double sourceRel) 
{
    this->rel = sourceRel;
}

void ComplexNumbers::setImg(double sourceImg)
{
    this->img = sourceImg;
}

double ComplexNumbers::getRel() const
{
    return this->rel;
}

double ComplexNumbers::getImg() const
{
    return this->img;
}

ComplexNumbers ComplexNumbers::operator+(const ComplexNumbers& rightSource) const
{
    ComplexNumbers result((this->rel + rightSource.rel),(this->img + rightSource.img));
    return result;
}

ComplexNumbers ComplexNumbers::operator+(double rigthSource) const
{
    ComplexNumbers result((this->rel + rigthSource), this->img);
    return result;
}

ComplexNumbers ComplexNumbers::operator-(const ComplexNumbers& rightSource) const
{
    ComplexNumbers result((this->rel - rightSource.rel),(this->img - rightSource.img));
    return result;
}

ComplexNumbers ComplexNumbers::operator-(double rigthSource) const
{
    ComplexNumbers result((this->rel - rigthSource), this->img);
    return result;
}

ComplexNumbers operator+(double left, const ComplexNumbers& right)
{
    ComplexNumbers result((left + right.rel), right.img);
    return result;
}

ComplexNumbers operator-(double left, const ComplexNumbers& right)
{
    ComplexNumbers result((left - right.rel), right.img);
    return result;
}

ComplexNumbers ComplexNumbers::operator*(const ComplexNumbers& source) const
{
    double resRel = this->rel * source.rel + this->img * source.img * -1;
    double resImg = this->rel * source.img + this->rel * source.img;
    ComplexNumbers result(resRel, resImg);

    return result;
}

ComplexNumbers ComplexNumbers::operator*(double source) const
{
    ComplexNumbers result(this->rel * source, this->img * source);
    return result;
}

ComplexNumbers operator*(double left, const ComplexNumbers& right)
{
    ComplexNumbers result(left * right.rel, left * right.img);
    return result;
}

void ComplexNumbers::operator=(const ComplexNumbers& source)
{
    this->rel = source.rel;
    this->img = source.img;
}

void ComplexNumbers::operator=(double source)
{
    this->rel = source;
    this->img = 0;
}

ComplexNumbers& ComplexNumbers::operator+=(const ComplexNumbers& source)
{
    this->rel += source.rel;
    this->img += source.img;
    return *this;
}

ComplexNumbers& ComplexNumbers::operator+=(double source)
{
    this->rel += source;
    return *this;
}

ComplexNumbers& ComplexNumbers::operator-=(const ComplexNumbers& source)
{
    this->rel -= source.rel;
    this->img -= source.img;
    return *this;
}

ComplexNumbers& ComplexNumbers::operator-=(double source)
{
    this->rel -= source;
    return *this;
}

ComplexNumbers& ComplexNumbers::operator++() 
{
    this->rel += 1;
    return *this;
}

ComplexNumbers ComplexNumbers::operator++(int)
{
    ComplexNumbers result(*this);
    this->rel += 1;
    this->img += 1;
    return result; 
}

ComplexNumbers& ComplexNumbers::operator--() 
{
    this->rel -= 1;
    return *this;
}

ComplexNumbers ComplexNumbers::operator--(int)
{
    ComplexNumbers result(*this);
    this->rel -= 1;
    this->img -= 1;
    return result; 
}




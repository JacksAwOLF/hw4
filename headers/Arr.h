#ifndef ARR_H
#define ARR_H

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Arr{
protected:
    vector<float> data;
    void checkSize (const Arr&);

public:
    Arr();
    Arr(const Arr&);
    Arr(int size);
    Arr(int size, istream&);

    // size of the array
    int size() const;

    // length of the vector
    float length();

    Arr copy();

    // change this vector to length 1
    Arr normalize();

    float operator[](int) const;
    float& operator[](int);

    // ops with other Arr
    Arr operator+(const Arr&);
    Arr operator-(const Arr&);
    Arr operator*(const Arr&);
    // float operator/(const Arr&);

    // ops with float
    Arr operator*(const float&);
    Arr operator/(const float&);

    // dot product
    float dot(const Arr&);
    Arr round();
};

istream& operator>>(istream&, Arr&);
ostream& operator<<(ostream&, const Arr&);

class Arr3: public Arr{
public:
    Arr3();
    Arr3(Arr);
    Arr3(istream&);
    Arr3(float, float, float);
    Arr3 cross(Arr3);
};

istream& operator>>(istream&, Arr3&);
ostream& operator<<(ostream&, const Arr3&);

class Arr4: public Arr{
public:
    Arr4();
    Arr4(Arr);
    Arr4(istream&);
    Arr4(Arr3, float);
    Arr4(float, float, float, float);
    Arr4 dehomogenize();
};

istream& operator>>(istream&, Arr4&);
ostream& operator<<(ostream&, const Arr4&);

#endif
#ifndef ARR_H
#define ARR_H

#include <iostream>
#include <vector>
using namespace std;

class Arr{
protected:
    vector<float> data;
    void checkSize(Arr&);

public:
    Arr();
    Arr(int size);
    Arr(int size, istream&);

    // size of the array
    int size() const;

    // length of the vector
    int length();

    // change this vector to length 1
    Arr normalize();

    float operator[](int) const;
    float& operator[](int);

    Arr operator+(Arr&);
    Arr operator-(Arr&);

    // TODO:
    // Arr operator+=(const Arr&);
    // Arr operator-=(const Arr&);

    float operator*(Arr&);
    Arr cross(Arr);

    Arr operator*(const float&);
    Arr operator/(const float&);
};

istream& operator>>(istream&, Arr&);
ostream& operator<<(ostream&, const Arr&);

class Arr3: public Arr{
public:
    Arr3();
    Arr3(istream&);
    Arr3(float, float, float);
    // TODO: Arr3 cross(Arr3);
};

istream& operator>>(istream&, Arr3&);
ostream& operator<<(ostream&, const Arr3&);

class Arr4: public Arr{
public:
    Arr4();
    Arr4(istream&);
    Arr4(Arr3, float);
    Arr4(float, float, float, float);
};

istream& operator>>(istream&, Arr4&);
ostream& operator<<(ostream&, const Arr4&);

#endif
#ifndef V3_H
#define V3_H

#include <iostream>
using namespace std;

class V3 {
public:
    float x, y, z;
    V3();
    V3(istream&);
    V3(float, float, float);

    V3 copy();
    float length();
    static V3 normalize(V3);

    V3 operator+(const V3&);
    V3 operator-(const V3&);

    float operator*(const V3&);
    V3 cross(const V3&);

    V3 operator*(const float&);
    V3 operator/(const float&);

    V3 getRound();
};

istream& operator>>(istream&, V3&);
ostream& operator<<(ostream&, const V3&);

#endif
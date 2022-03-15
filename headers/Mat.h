#ifndef MAT_H
#define MAT_H

#include "Arr.h"

// TODO: general Matrix class

class Mat4{
public:
    vector<Arr4> data;
    Mat4();
    Mat4(float*);

    Mat4 operator+(const Mat4&);
    Mat4 operator*(const float&);
    Arr4 operator*(const Arr4&);
    Mat4 operator*(const Mat4&);

    static Mat4 identity();
};

ostream& operator<<(ostream&, const Mat4&);

#endif
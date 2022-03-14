#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Mat.h"
#include "Arr.h"

class Transform{
public:
    Mat4 matrix, inverse;

    Transform();
    Transform(float* mat, float* inv);
    Transform(Mat4 mat, Mat4 inv);

    Transform operator*(const Transform &o);

    static Transform identity();
    static Transform inScale(istream&);
    static Transform inTranslate(istream&);
    // TODO!!!
    // static Transform inRotate(istream&);
};

#endif
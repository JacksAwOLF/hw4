#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Mat.h"
#include "Arr.h"

class Transform{
public:
    Mat4 matrix, inverse;

    Transform();
    Transform(Mat4 mat, Mat4 inv);

    Transform operator*(Transform &o);

    static Transform inScale(istream&);
    // TODO!!!
    // static Transform inRotate(istream&);
    static Transform inTranslate(istream&);
};

#endif
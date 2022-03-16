#include "Transform.h"

// constructors

Transform::Transform(){
    matrix = Mat4::identity();
    inverse = Mat4::identity();
}

Transform::Transform(float* mat, float* inv){
    matrix = Mat4(mat);
    inverse = Mat4(inv);
}

Transform::Transform(Mat4 mat, Mat4 inv){
    matrix = mat;
    inverse = inv;
}

// multiply functions

Transform Transform::operator*(Transform &o){
    return Transform(
        matrix.mult(o.matrix),
        o.inverse.mult(inverse)
    );
}

Arr3 Transform::multNormal(const Arr3& normalVec){
    // inverse transpose, in that order
    return inverse.transpose() * Arr4(normalVec, 0);
}

// static transformations (and their inverses)

Transform Transform::identity(){
    return Transform(Mat4::identity(), Mat4::identity());
}

Transform Transform::inScale(istream& in){
    Arr3 scale(in);
    float mat[16] = {
        scale[0], 0.0, 0.0, 0.0,
        0.0, scale[1], 0.0, 0.0,
        0.0, 0.0, scale[2], 0.0,
        0.0, 0.0, 0.0, 1.0
    };
    float inv[16] = {
        1/scale[0], 0.0, 0.0, 0.0,
        0.0, 1/scale[1], 0.0, 0.0,
        0.0, 0.0, 1/scale[2], 0.0,
        0.0, 0.0, 0.0, 1.0
    };
    return Transform(mat, inv);
}

Transform Transform::inTranslate(istream& in){
    Arr3 delta(in);
    float mat[16] = {
        1.0, 0.0, 0.0, delta[0],
        0.0, 1.0, 0.0, delta[1],
        0.0, 0.0, 1.0, delta[2],
        0.0, 0.0, 0.0, 1.0
    };
    float inv[16] = {
        1.0, 0.0, 0.0, -delta[0],
        0.0, 1.0, 0.0, -delta[1],
        0.0, 0.0, 1.0, -delta[2],
        0.0, 0.0, 0.0, 1.0
    };
    return Transform(mat, inv);
}

// TODO: understand this better
Transform Transform::inRotate(istream& in){
    Arr3 normal(in);
    float angle; in >> angle;

    normal = normal.normalize();
    angle = angle * 3.1415926535 / 180.0;

    float t2[16] = {
        0.0, normal[2], -normal[1], 0.0,
        -normal[2], 0.0, normal[0], 0.0,
        normal[1], -normal[0], 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    Mat4 T2(t2), TT2;
    TT2 = T2.mult(T2);
    Mat4 res = Mat4::identity() + 
        T2 * sin(angle) + TT2 * (1-cos(angle));
    
    // make sure the last col / row is 0001
    for (int i=0; i<4; i++) {
        res.data[3][i] = (i+1)/4;
        res.data[i][3] = (i+1)/4;
    }

    return Transform(res.transpose(), res);
    // return Transform(res, res.transpose());
}
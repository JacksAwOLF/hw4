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

// multiply with self function

Transform Transform::operator*(const Transform &o){
    return Transform(
        matrix * o.matrix,
        inverse * o.inverse
    );
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

// TODO!!!
// Transform Transform::inRotate(istream& in){
//     Arr3 normal(in);
//     float angle; in >> angle;
//     // Arr3 n = normal.normalize();
//     angle = angle * 3.1415926535 / 180.0;


// }
#include "Mat.h"

Mat4::Mat4(){
    *this = Mat4::identity();
}

Mat4::Mat4(float* x){
    for (int i=0; i<4; i++)
        data.push_back(
            Arr4(x[i*4], x[i*4+1], x[i*4+2], x[i*4+3]));
}

Mat4 Mat4::operator+(const Mat4& o){
    float res[16];
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            res[i*4+j] = data[i][j] + o.data[i][j];
    return Mat4(res);
}

Mat4 Mat4::operator*(const float& o){
    float res[16];
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            res[i*4+j] = data[i][j] * o;
    return Mat4(res);
}

Arr4 Mat4::operator*(const Arr4& o){
    float res[4] = {0, 0, 0, 0};
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            res[i] += data[i][j] * o[j];
    return Arr4(res[0], res[1], res[2], res[3]);
}

Mat4 Mat4::operator*(const Mat4& o){
    float res[16];
    for (int i=0; i<16; i++)
        res[i] = 0;
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            for (int k=0; k<4; k++)
                res[i*4+j] += data[i][k] * o.data[k][j];
    return Mat4(res);
}

// static method to generate identity

Mat4 Mat4::identity(){
    float res[16] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
    return Mat4(res);
}

ostream& operator<<(ostream& out, const Mat4& o){
    out<<endl;
    for (int i=0; i<4; i++)
        out<<o.data[i]<<endl;
    return out;
}
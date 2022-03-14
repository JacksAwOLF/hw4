#include "transform.h"

// constructors

Transform::Transform(){}
Transform::Transform(float* res){
    cout<<"creating tf from arr: ";
    for (int i=0; i<16; i++)
        cout<<res[i]<<" ";
    cout<<endl;
    from(res);
}

// some basic Transform arithmetic

Transform Transform::operator*(const float& x){
    float res[16];
    for (int i=0; i<16; i++)
        res[i] = mat[i] * x;
    return Transform(res);
}

Transform Transform::operator+(const Transform& o){
    float res[16];
    for (int i=0; i<16; i++)
        res[i] = mat[i] + o.mat[i];
    return Transform(res);
}

// basic functionalities

void Transform::from(float* res){
    for (int i=0; i<16; i++)
        mat[i] = res[i];
}

Transform Transform::copy(){
    return Transform(mat);
}

void Transform::multiply(Transform o){
    float res[16];
    for (int i=0; i<16; i++){
        res[i] = 0.0;
        for (int j=0; j<4; j++){
            // TODO: why does commenting these debug
            // statements crash the program?
            // printf("%d += %d * %d => %f * %f = %f; %f\n",
            //     i, i/4*4+j, j*4+i%4, mat[i/4*4+j], o.mat[j*4+i%4],
            //      mat[i/4*4+j] * o.mat[j*4+i%4], res[i]
            // );
            res[i] += mat[i/4*4+j] * o.mat[j*4+i%4];
        }
    }
    from(res);
}

V3 Transform::multPoint(V3 point){
    // cout<<"calling multpoint\n";
    float res[4];
    for (int i=0; i<4; i++)
        res[i] = V3(mat[i*4], mat[i*4+1], mat[i*4+2]) * point + mat[i*4+3];
    if (res[3] != 0)
        for (int i=0; i<3; i++)
            res[i] = res[i] / res[3];
    // cout<<"finish multpoint\n";
    return V3(res[0], res[1], res[2]);
}

// static functions

Transform Transform::identity(){
    float res[16] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
    return Transform(res);
}

Transform Transform::scale(V3 factor){
    cout<<"creating transform scale "<<factor<<endl;
    float res[16] = {
        factor.x, 0.0, 0.0, 0.0,
        0.0, factor.y, 0.0, 0.0,
        0.0, 0.0, factor.z, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
    return Transform(res);
}

// TODO: understnad this better
Transform Transform::rotate(V3 normal, float angle){
    
    normal = V3::normalize(normal);
    angle = angle * 3.1415926535 / 180.0;

    float t2[16] = {
        0.0, normal.z, -normal.y, 0.0,
        -normal.z, 0.0, normal.x, 0.0,
        normal.y, -normal.x, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0
    };

    Transform T2(t2), TT2(t2);
    TT2.multiply(T2);
    Transform res = Transform::identity() + 
        T2 * sin(angle) + TT2 * (1-cos(angle));
    
    // make sure the last col / row is 0001
    for (int i=0; i<4; i++) {
        res.mat[12+i] = (i+1)/4;
        res.mat[3+i*4] = (i+1)/4;
    }

    return res;
}

Transform Transform::translate(V3 delta){
    cout<<"creating translate scale "<<delta<<endl;
    float res[16] = {
        1.0, 0.0, 0.0, delta.x,
        0.0, 1.0, 0.0, delta.y,
        0.0, 0.0, 1.0, delta.z,
        0.0, 0.0, 0.0, 1.0
    };
    return Transform(res);
}

// better IO
Transform Transform::readInScale(istream& in){
    return Transform::scale(V3(in));
}
Transform Transform::readInRotate(istream& in){
    V3 normal(in);
    float angle; in>>angle;
    return Transform::rotate(normal, angle);
}
Transform Transform::readInTranslate(istream& in){
    return Transform::translate(V3(in));
}

ostream& operator<<(ostream& os, const Transform& tf) {
    os<<endl;
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++)
            os<<tf.mat[i*4+j]<<" ";
        os<<endl;
    }
    os<<endl;
    return os;
}

// inverse calculation

// TODO
Transform Transform::inverse(){
    float res[16];

    // switch rows around until every mat[i,i] is not 0

    // subtract rows s.t. botright triangle is all 0

    // subtract rows s.t. all other values except [i,i] are 0

    // scale the [i,i] values to 1

    return Transform(res);
}
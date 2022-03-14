#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "v3.h"
#include <math.h>

class Transform{
private:
    // inverse of a matrix god help me
    bool calcInv;
    float inv[16], invHelp[16];
    void switchRow(int, int);
    void switchCol(int, int);
    void multRow(int);
    void multCol(int);
    void subRowFromRow(int, int);
    void subColFromCol(int, int);
    int maxIndInRow(int);
    int maxIndInCol(int);

public:
    float mat[16];
    Transform();
    Transform(float*);

    Transform copy();
    void from(float*);
    void multiply(Transform);
    V3 multPoint(V3);
    Transform inverse();

    Transform operator*(const float&);
    Transform operator+(const Transform& o);

    static Transform identity();
    static Transform scale(V3 factor);
    static Transform rotate(V3 normal, float angle);
    static Transform translate(V3 delta);

    static Transform readInScale(istream&);
    static Transform readInRotate(istream&);
    static Transform readInTranslate(istream&);
};

ostream& operator<<(ostream&, const Transform&);

#endif
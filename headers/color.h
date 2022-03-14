#ifndef COLOR_H
#define COLOR_H

#include "v3.h"
#include <vector>

class Color {
private:
public:
    V3 ambient, diffuse, specular, emission;
    float shininess;

    static vector<float*> lightpos;
    static vector<V3> lightcol;
    static vector<V3> atten;

    Color();
    // Color(V3 amb);

    Color copy();

    V3 calculate(V3 point);
};

#endif
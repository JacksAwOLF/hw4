#ifndef LIGHT_H
#define LIGHT_H

#include "Arr.h"
#include "ShadingVars.h"
#include "Intersection.h"
#include <cmath>

class Light{
public:
    Arr3 position, color;
    bool directional;
    Arr3 attenuation;

    Light(istream&, bool dir, Arr3 atten);
    Arr3 shade(Intersection hit, Arr3 eyedir, Arr3 normal);
};

#endif
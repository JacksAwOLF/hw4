#ifndef LIGHT_H
#define LIGHT_H

#include "Arr.h"
#include "Intersection.h"
#include <cmath>

// simple class to contain all the vars
// neede to shade objects
class ShadingVars{
public:
    Arr3 ambience, emission;
    Arr3 diffuse, specular;
    float shininess;
    ShadingVars();
};

class Light{
private:
    Arr3 position, color;
    bool directional;
    Arr3 attenuation;

public:
    Light(istream&, bool dir);
    Arr3 color(Intersection hit, Arr3 eye);
};

#endif
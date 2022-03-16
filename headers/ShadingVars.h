#ifndef SHADINGVARS_H
#define SHADINGVARS_H

#include "Arr.h"

// simple class to contain all the vars
// neede to shade objects
class ShadingVars{
public:
    Arr3 ambience, emission;
    Arr3 diffuse, specular;
    float shininess;
    ShadingVars();
};

#endif
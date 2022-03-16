#include "ShadingVars.h"

ShadingVars::ShadingVars(){
    ambience = Arr3(0.2, 0.2, 0.2);
    emission = Arr3();
    diffuse = Arr3();
    specular = Arr3();
    shininess = 0.0;
}
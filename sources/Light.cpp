#include "Light.h"

Light::Light(istream &in, bool dir, Arr3 atten){
    in >> position >> color;
    directional = dir;
    attenuation = atten;
}

Arr3 Light::shade(Intersection hit, Arr3 eyedir, Arr3 normal){

    ShadingVars sVars = hit.obj->shadingVars;
    
    Arr3 direction = directional ? position.normalize() : 
            (position - (hit.pos)).normalize(),
        halfAngle = (direction + (eyedir)).normalize();
    
    Arr3 lambert = sVars.diffuse * max((float)0.0, normal.dot(direction));
    Arr3 phong = sVars.specular * 
        pow(max((float)0.0, normal.dot(halfAngle)), sVars.shininess);

    float r = (hit.pos - (this->position)).length(),
        atten = directional ? 1 : attenuation.dot(Arr3(1, r*r, r*r*r));

    Arr3 res = (color / atten) * (lambert + phong);
    
    return res.between(0.0, 1.0);
}
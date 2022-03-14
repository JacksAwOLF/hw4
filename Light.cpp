#include "Light.h"

ShadingVars::ShadingVars(){
    ambience = Arr3(0.2, 0.2, 0.2);
    emission = Arr3();
    diffuse = Arr3();
    specular = Arr3();
    shininess = 0.0;
}

Light::Light(istream &in, bool dir){
    in >> position >> color;
    directional = dir;
}

Arr3 Light::color(Intersection hit, Arr3 eye){

    ShadingVars sVars = hit.obj.shadingVars;
    
    Arr3 normal = hit.obj->surfaceNormal(hit.pos),
        eyedir = hit.pos - eye,
        direction = directional ? position : position - hit.pos,
        halfAngle = direction + eyedir;
    
    Arr3 lambert = sVars.diffuse * max(0, normal * direction);
    Arr3 phong = sVars.specular * 
        pow(max(0, normal * halfAngle), sVars.shininess);

    float r = (hit.pos - this->position).length(),
        atten = attenuation * Arr3(1, r*r, r*r*r);

    return (color / atten) * (lambert + phong);
}

// float nDotL = dot(normal, direction)  ;         
// vec4 lambert = diffuse * lightcol * max (nDotL, 0.0) ;  

// float nDotH = dot(normal, halfvec) ; 
// vec4 phong = specular * lightcol * pow (max(nDotH, 0.0), shininess) ; 

// vec4 retval = lambert + phong ; 
// return retval ;
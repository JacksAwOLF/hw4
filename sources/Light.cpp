#include "Light.h"

Light::Light(istream &in, bool dir, Arr3 atten){
    in >> position >> color;
    directional = dir;
    attenuation = atten;
}

Arr3 Light::shade(Intersection hit, Arr3 eye){

    ShadingVars sVars = hit.obj->shadingVars;
    
    Arr3 normal = hit.obj->surfaceNormal(hit.pos).normalize(),
        eyedir = (eye - (hit.pos)).normalize(),
        direction = directional ? position.normalize() : 
            (position - (hit.pos)).normalize(),
        halfAngle = (direction + (eyedir)).normalize();
    
    Arr3 lambert = sVars.diffuse * max((float)0.0, normal.dot(direction));
    Arr3 phong = sVars.specular * 
        pow(max((float)0.0, normal.dot(halfAngle)), sVars.shininess);

    float r = (hit.pos - (this->position)).length(),
        atten = directional ? 1 : attenuation.dot(Arr3(1, r*r, r*r*r));

    Arr3 res = (color / atten) * (lambert + phong);
    
    // if (res.length() < 0.1){
    //     cout<<"shading: return "<<res<<" lambert: ";
    //     cout<<lambert<<" phong: "<<phong<<endl;
    // }

    return res.between(0.0, 1.0);
}

// float nDotL = dot(normal, direction)  ;         
// vec4 lambert = diffuse * lightcol * max (nDotL, 0.0) ;  

// float nDotH = dot(normal, halfvec) ; 
// vec4 phong = specular * lightcol * pow (max(nDotH, 0.0), shininess) ; 

// vec4 retval = lambert + phong ; 
// return retval ;
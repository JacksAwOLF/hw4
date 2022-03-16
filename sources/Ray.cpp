#include "Ray.h"

Ray::Ray(Arr3 a, Arr3 b, bool to){
    start = a;
    if (to) slope = b - a;
    else slope = b;
    
    slopeInv = slope.inverse();
}

Arr3 Ray::at(float t){
    return start + slope * t;
}

float Ray::getT(Arr3 point){
    Arr3 p = point - start;
    return p.length() / slope.length();
}

Ray Ray::transform(Mat4 mat){
    return Ray(mat * Arr4(start, 1), mat * Arr4(slope, 0), false);
}

ostream& operator<<(ostream& out, const Ray& r){
    return out<<r.start<<" + t * "<<r.slope;
}

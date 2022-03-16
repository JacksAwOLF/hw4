#ifndef RAY_H
#define RAY_H

#include "Arr.h"
#include "Mat.h"

// a simple class for data storage
class Ray{
public:
    Arr3 start, slope;
    Arr3 slopeInv; // for quick bounding box calc

    Ray(Arr3 a, Arr3 b, bool to=true);
    Arr3 at(float t);
    float getT(Arr3 point);
    Ray transform(Mat4);
};

ostream& operator<<(ostream& out, const Ray& r);

#endif
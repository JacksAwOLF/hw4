#ifndef OBJ_H
#define OBJ_H

#include "Arr.h"
#include "ShadingVars.h"
#include "Transform.h"
#include "Ray.h"
#include <cmath>

class Obj {
public:
    ShadingVars shadingVars;
    Transform transform;

    Obj(ShadingVars svars, Transform tf);

    // returns t, where if positive, means that the Ray first intersects
    // this object at ray.a + ray.b * t
    virtual float intersectWithRay(Ray);

    // returns surface normal at point of intersection
    virtual Arr3 surfaceNormal(Arr3 pointOfInt);
};

class Triangle: public Obj {
private:
    Arr3 a, b, c;

    // aa.cross(bb) = normal vector to plane
    Arr3 aa, bb, n; 
    // TODO: could save more vars here in intersection calculation

public:
    Triangle(istream&, vector<Arr3>&, ShadingVars, Transform);
    
    float intersectWithRay(Ray);
    Arr3 surfaceNormal(Arr3 pointOfInt);
};

class Sphere: public Obj {
private:
    Arr3 center;
    float radius;
public:
    Sphere(istream&, ShadingVars, Transform);
    float intersectWithRay(Ray);
    Arr3 surfaceNormal(Arr3 pointOfInt);
};

#endif
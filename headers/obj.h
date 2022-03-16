#ifndef OBJ_H
#define OBJ_H

#include "Arr.h"
#include "ShadingVars.h"
#include "Transform.h"
#include "Ray.h"
#include <cmath>

class Obj {
public:
    bool debug;
    ShadingVars shadingVars;
    Transform transform;

    Obj(ShadingVars svars, Transform tf);

    // returns t, where if positive, means that the Ray first intersects
    // this object at ray.a + ray.b * t
    virtual bool intersectWithRay(Ray, Arr3&);

    // returns surface normal at point of intersection
    virtual Arr3 surfaceNormal(Arr3 pointOfInt);
};

class Triangle: public Obj {
private:
    Arr3 a, b, c;

    // aa.cross(bb) = normal vector to plane
    Arr3 aa, bb, n; 
    Arr3 n_aa, aap;
    float bbDotaap, bbDotn_aa;

public:
    Triangle(istream&, vector<Arr3>&, ShadingVars, Transform);

    bool intersectWithRay(Ray, Arr3&);
    Arr3 surfaceNormal(Arr3);
};

class Sphere: public Obj {
private:
    Arr3 center;
    float radius;
public:
    Sphere(istream&, ShadingVars, Transform);

    bool intersectWithRay(Ray, Arr3&);
    Arr3 surfaceNormal(Arr3);
};

#endif
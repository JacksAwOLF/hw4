#ifndef OBJ_H
#define OBJ_H

#include "v3.h"
#include "scene.h"
#include "color.h"
#include "transform.h"
#include <math.h>
#include <string>

class VirtualObj {
public:
    Color color;
    Transform transform;

    VirtualObj() {}
    virtual string getName();

    // returns t, where if positive, means that the Ray first intersects
    // this object at ray.a + ray.b * t
    virtual float intersectWithRay(Ray);
};

class Triangle: public VirtualObj {
private:
    V3 a, b, c;
    V3 aa, bb, n; // n is normal, aa bb is for n calculation
public:
    Triangle(istream&, vector<V3>&, Color, Transform);
    string getName();
    float intersectWithRay(Ray);
};

class Sphere: public VirtualObj {
private:
    V3 center;
    float r;
public:
    Sphere(istream&, Color, Transform);
    string getName();
    float intersectWithRay(Ray);
};

#endif
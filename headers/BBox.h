#ifndef BBOX_H
#define BBOX_H

#include "Ray.h"
#include "Mat.h"

#define MIN(a, b) (a<b?a:b)
#define MAX(a, b) (a<b?b:a)

class BBox{
public:
    Arr3 mins, maxs;
    BBox();
    bool intersectRay(Ray);
    void transform(Mat4);
};

#endif
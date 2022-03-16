#ifndef BBOX_H
#define BBOX_H

#include "Ray.h"

class BBox{
public:
    Arr3 mins, maxs;
    BBox();
    bool intersectRay(Ray);
};

#endif
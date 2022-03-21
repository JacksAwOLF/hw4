#include "BBox.h"

BBox::BBox(){}

bool BBox::intersectRay(Ray ray){
    
    // float maxofmins = -INF;
    // float minofmaxs = +INF;
    float t1, t2, mint[3], maxt[3];

    Arr3 minDis = mins - ray.start, maxDis = maxs - ray.start;

    t1 = minDis[0] * ray.slopeInv[0];
    t2 = maxDis[0] * ray.slopeInv[0];
    mint[0] = MIN(t1, t2);
    maxt[0] = MAX(t1, t2);

    t1 = minDis[1] * ray.slopeInv[1];
    t2 = maxDis[1] * ray.slopeInv[1];
    mint[1] = MIN(t1, t2);
    maxt[1] = MAX(t1, t2);

    t1 = minDis[2] * ray.slopeInv[2];
    t2 = maxDis[2] * ray.slopeInv[2];
    mint[2] = MIN(t1, t2);
    maxt[2] = MAX(t1, t2);

    float maxofmins = MAX(mint[0], mint[1]);
    maxofmins = MAX(maxofmins, mint[2]);
    float minofmaxs = MIN(maxt[0], maxt[1]);
    minofmaxs = MIN(minofmaxs, maxt[2]);
    
    return maxofmins <= minofmaxs;
}

void BBox::transform(Mat4 matrix){
    mins = matrix * Arr4(mins, 1);
    maxs = matrix * Arr4(maxs, 1);
}
#include "BBox.h"

BBox::BBox(){}

bool BBox::intersectRay(Ray ray){
    
    float maxofmins = -INF;
    float minofmaxs = +INF;

    Arr3 minDis = mins - ray.start, maxDis = maxs - ray.start;

    // cout<<"BBOx: "<<mins<<" and "<<maxs<<", ray "<<ray<<endl;

    for (int i=0; i<3; i++){
        float t1 = minDis[i] * ray.slopeInv[i];
        float t2 = maxDis[i] * ray.slopeInv[i];
        maxofmins = max(maxofmins, min(t1, t2));
        minofmaxs = min(minofmaxs, max(t1, t2));
        // cout<<"for "<<i<<"dim, "<<t1<<" "<<t2<<endl;
    }

    
    // cout<<"result: "<<maxofmins<<"<="<<minofmaxs<<endl;
    return maxofmins <= minofmaxs;
}
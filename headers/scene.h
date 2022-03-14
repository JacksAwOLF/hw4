#ifndef SCENE_H
#define SCENE_H

#include "v3.h"
#include <vector>
#include <sstream>
#include <math.h>

// a ray with formula p=a+b*t
struct Ray {
public:
    V3 a, b;
    // construct a ray that shoots from from to to
    Ray(V3 from, V3 to);
    V3 getPoint(float t);
};

class Scene {
private:
    V3 eye, up, at;   // general glu_lookat coordinates;
    V3 hor, ver, dis; // true co-ordinates from camera
    float foy;
public:
    float w, h;
    void setCamera(istream&);
    void setScreen(istream&);
    vector<Ray> getRays();
};

#endif
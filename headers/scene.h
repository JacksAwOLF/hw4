#ifndef SCENE_H
#define SCENE_H

#include "Arr.h"
#include "Camera.h"
#include "Ray.h"
#include "Obj.h"
#include "Light.h"
#include "Intersection.h"

#include <iostream>
#include <string>
#include <math.h>

class Scene{
public:
    bool debug;

    int imageW, imageH;
    int maxdepth;
    Camera cam;
    PixelSize pixelSize;
    Arr3 screenTopLeft, attenuation;
    string outfile;

    vector<Obj*> objs;
    vector<Light> lights;
    vector<vector<Arr3>> image;

    Scene();

    void setImage(istream&);
    void setCamera(istream&);
    void setFile(string);
    
    void addLight(istream&, bool);

    Intersection firstObjHit(Ray);
    void render();
};

#endif
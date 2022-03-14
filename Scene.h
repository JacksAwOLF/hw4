#ifndef SCENE_H
#define SCENE_H

#include "Arr.h"
#include "Camera.h"
#include "Ray.h"
#include "Obj.h"
#include "Light.h"
#include "Intersection.h"


#include <iostream>
#include <math.h>


class Scene{
    Camera cam;
    vector<Ray> rays;
    vector<Obj> objs;
    vector<Light> lights;
    int imageW, imageH;
    float screenW, screenH;
    Arr3 pixelW, pixelH;
    vector<vector<Arr3>> image;

    void setCamera(istream&);
    void setImage(istream&);

    void shadePixel();
    Intersection firstObjHit(Ray);

    void render(){
        Arr3 curPos;
        for (int i=0; i<imageH; i++){
            curPos = screenTopLeft + pixelH * i;
            for (int j=0; j<imageW; j++){
                
                // construct ray that goes through this pixel
                Ray ray(eye, curPos);
                curPos += pixelW;

                // find first obj this ray hits
                Intersection hit = firstObjHit(ray);
                if (hit.obj != nullptr) {

                    // color with each light source if needed
                    for (Light light : lights){
                        Ray ltRay(hit.pos, light.pos);
                        if (firstObjHit(ltRay).obj == nullptr) {
                            image[i][j] += light.color(hit);
                        }
                    }
                }
            }
        }
    }
};

#endif
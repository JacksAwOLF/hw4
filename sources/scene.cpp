#include "Scene.h"

Scene::Scene(){
    maxdepth = 5;
    outfile = "test.ppm";
    attenuation = Arr3(1, 0, 0);
}

void Scene::setImage(istream& in){
    in >> imageW >> imageH;
}

void Scene::setCamera(istream& in){
    cam = Camera(in);
    pixelSize = cam.calculatePixelSize(imageW, imageH);
    screenTopLeft = cam.at 
        - pixelSize.pixelW * imageW / 2
        - pixelSize.pixelH * imageH / 2;
}

void Scene::addLight(istream& in, bool dir){
    lights.push_back(Light(in, dir, attenuation));
}

Intersection Scene::firstObjHit(Ray ray){
    // don't count 0s, better for shadow rays
    float t = 0;
    Obj *obj = nullptr;
    for (int i=0; i<objs.size(); i++){
        float tt = objs[i]->intersectWithRay(ray);
        if (tt > 0 && (t == 0 || tt < t)){
            t = tt;
            obj = objs[i];
        }
    }
    
    return Intersection(obj, ray.at(t));
}

void Scene::render(){
    Arr3 curPos;
    for (int i=0; i<imageH; i++){
        curPos = screenTopLeft + pixelSize.pixelH * i;
        for (int j=0; j<imageW; j++){
            
            // construct ray that goes through this pixel
            Ray ray(cam.eye, curPos);
            curPos = curPos + pixelSize.pixelW;

            // find first obj this ray hits
            Intersection hit = firstObjHit(ray);
            if (hit.obj != nullptr) {

                // color with each light source if needed
                for (Light light : lights){
                    Ray ltRay(hit.pos, light.position);
                    if (firstObjHit(ltRay).obj == nullptr) {
                        image[i][j] = image[i][j] + light.shade(hit, cam.eye);
                    }
                }
            }
        }
    }
}
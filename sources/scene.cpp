#include "Scene.h"

Scene::Scene(){
    maxdepth = 5;
    outfile = "test.ppm";
    attenuation = Arr3(1, 0, 0);
}

void Scene::setImage(istream& in){
    in >> imageW >> imageH;
    for (int i=0; i<imageH; i++){
        vector<Arr3> row;
        for (int j=0; j<imageW; j++)
            row.push_back(Arr3(0, 0, 0));
        image.push_back(row);
    }
    cout<<"set image "<<imageW<<" "<<imageH<<endl;
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
    Arr3 point;
    for (int i=0; i<objs.size(); i++){
        Arr3 pp;
        // cout<<"befbef: "<<ray<<endl;
        if (!objs[i]->intersectWithRay(ray, pp))
            continue;
        // cout<<"aftaft: "<<ray<<endl;

        float tt = ray.getT(pp);
        if (tt > 1e-6 && (t == 0 || tt < t)){
            // cout<<"hit at time "<<tt<<", position "<<pp<<endl;
            t = tt;
            obj = objs[i];
            point = pp;
        }
    }
    
    return Intersection(obj, point);
}

void Scene::render(){
    Arr3 curPos;
    long long counter = 0, counttill = 5000;
    for (int i=0; i<imageH; i++){
        curPos = screenTopLeft + pixelSize.pixelH * i;
        for (int j=0; j<imageW; j++){
            
            // cout<<"ray through "<<curPos + pixelSize.pixelMid<<endl;

            // construct ray that goes through this pixel
            Ray ray(cam.eye, curPos + pixelSize.pixelMid, true);
            curPos = curPos + pixelSize.pixelW;

            // find first obj this ray hits
            // cout<<"ray before: "<<ray<<endl;
            Intersection hit = firstObjHit(ray);
            // cout<<"ray after: "<<ray<<endl;

            if (hit.obj != nullptr) {
                // color with each light source if needed

                image[i][j] = hit.obj->shadingVars.ambience +
                    hit.obj->shadingVars.emission;

                for (Light light : lights){
                    Ray ltRay(hit.pos, light.position, true);

                    // cout<<"hit lt ray "<<ltRay<<endl;
                    Intersection hit2 = firstObjHit(ltRay);
                    if (hit2.obj == nullptr) {
                        image[i][j] = image[i][j] + light.shade(hit, cam.eye);
                    }
                    // else {
                    //     // cout<<"so waht did you hit "<<
                    //     //     hit.pos<<" and "<<
                    //     //     hit2.pos<<endl;
                    // }
                }
                
            }
            

            // progress counter
            if (++counter % counttill == 0){
                cout<<"rendering "<<counter<<"/"<<(long long)imageW * imageH<<endl;
            }
        }
    }
}
#include "Scene.h"
#include <omp.h>

Scene::Scene(){
    debug = false;
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
    // int count = 0;
    for (int i=0; i<objs.size(); i++){
        // cout<<i<<" obj\n";
        Arr3 pp;

        if (debug) objs[i]->debug = true;
        if (!objs[i]->intersectWithRay(ray, pp)){
            if (debug) objs[i]->debug = false;
            continue;
        }
        if (debug) objs[i]->debug = false;

        float tt = ray.getT(pp);

        if (debug) cout<<"found obj with int at "<<pp<<" time "<<tt<<endl;

        if (tt > 1e-6 && (t == 0 || tt < t)){

            // count++;
            // if (count > 1){
            //     // cout<<"hit at time "<<tt<<", position "<<pp<<endl;
            //     // cout<<"compare with "<<t<<endl;
            // }

            t = tt;
            obj = objs[i];
            point = pp;

            if (debug) cout<<"update "<<t<<": "<<point<<endl;
        }
    }
    
    return Intersection(obj, point);
}

void Scene::render(){
    
    long count = 0, counttill = 1000;
    
    // preprocess all the rays
    // vector<Ray> rays;
    // Arr3 curPos;
    // for (long k=0; k<imageW*imageH; k++){
    //     if (k%imageW == 0)
    //         curPos = screenTopLeft + pixelSize.pixelH * (k/imageW);
    //     rays.push_back(Ray(cam.eye, curPos + pixelSize.pixelMid, true));
    //     curPos = curPos + pixelSize.pixelW;
    // }

    #pragma omp parallel for
    for (long k=0; k<imageW*imageH; k++){
        int i = k / imageW;
        int j = k % imageW;

        // find first obj this ray hits
        Ray ray(cam.eye, screenTopLeft + pixelSize.pixelH * i 
            + pixelSize.pixelW * j + pixelSize.pixelMid, true);
        Intersection hit = firstObjHit(ray);

        if (hit.obj != nullptr) {

            // cout<<k<<" hit1 sth\n";

            // material color
            image[i][j] = hit.obj->shadingVars.ambience +
                hit.obj->shadingVars.emission;

            // cout<<k<<" hit2 sth\n";

            // light shading color
            for (Light light : lights){
                // cout<<"lt1\n";

                Ray ltRay(hit.pos, light.position, true);
                Intersection hit2 = firstObjHit(ltRay);
                // cout<<"lt2\n";
                if (hit2.obj == nullptr) {
                    // cout<<"lt2.5\n";
                    image[i][j] = image[i][j] + light.shade(hit, cam.eye);
                    // cout<<"lt2.8\n";
                }

                else {
                    cout<<"first intersection at "<<hit.pos<<" with ray "<<ray<<endl; 
                    cout<<"ltray: "<<ltRay<<endl<<"hit point ";
                    cout<<hit2.pos<<" t: "<<ltRay.getT(hit2.pos)<<endl;
                    debug = true;
                    firstObjHit(ltRay);
                    debug = false;
                }
                // cout<<"lt3\n";
            }
        }

        // progress counter
        #pragma omp critical
        if (++count % counttill == 0)
            cout<<"rendering "<<outfile<<": "<<count<<"/"<<(long long)imageW * imageH<<endl;
        
    }
}
#include "Scene.h"
#include <omp.h>

Scene::Scene(){
    debug = false;
    maxDepth = 5;
    outfile = "test.png";
    attenuation = Arr3(1, 0, 0);
}

void Scene::setFile(string file){
    outfile = file;
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
    float t = 0;
    Obj *obj = nullptr;
    Arr3 point;
    // int count = 0;
    for (int i=0; i<objs.size(); i++){
        // cout<<i<<" obj\n";
        Arr3 pp;

        // if (debug) objs[i]->debug = true;

        if (!objs[i]->touchBox(ray)){
            continue;
        }

        if (!objs[i]->intersectWithRay(ray, pp)){
            // if (debug) objs[i]->debug = false;
            continue;
        }
        // if (debug) objs[i]->debug = false;

        float tt = ray.getT(pp);

        // if (debug) 
        // cout<<"found obj with int at "<<pp<<" time "<<tt<<endl;

        if (tt > TOLERANCE && (t == 0 || tt < t)){

            // count++;
            // if (count > 1){
            //     // cout<<"hit at time "<<tt<<", position "<<pp<<endl;
            //     // cout<<"compare with "<<t<<endl;
            // }

            t = tt;
            obj = objs[i];
            point = pp;

            // if (debug) cout<<"update "<<t<<": "<<point<<endl;
        }
    }
    
    return Intersection(obj, point);
}

Arr3 Scene::shootRay(Ray ray, int depth){
    
    Arr3 res;
    if (depth == maxDepth) 
        return res;
    
    Intersection hit = firstObjHit(ray);

    if (hit.obj != nullptr) {

        // material color
        res.add(hit.obj->shadingVars.ambience + 
            (hit.obj->shadingVars.emission));

        // light shading color
        Arr3 normal = hit.obj->surfaceNormal(hit.pos).normalize(),
            eyedir = (cam.eye - hit.pos).normalize();

        for (Light light : lights){
            Ray ltRay(hit.pos, light.position, !light.directional);
            Intersection hit2 = firstObjHit(ltRay);
            bool toShade =
                hit2.obj == nullptr || 
                (!light.directional && 
                    (hit2.pos-(hit.pos)).length() > 
                    (light.position-(hit.pos)).length());
            if (toShade){
                res.add(light.shade(hit, eyedir, normal));
            }
        }

        // reflection color
        Arr3 destroyCPU = hit.obj->shadingVars.specular;
        if (destroyCPU.length() > 0) {
            Arr3 from = (hit.pos - cam.eye).normalize();
            Ray rfRay(hit.pos, from - (normal * from.dot(normal) * 2), false);
            res.add(shootRay(rfRay, depth+1) * destroyCPU);
        }
    }

    return res;
}

void Scene::render(){
    
    long count = 0, counttill = 1000;
    
    #pragma omp parallel for
    for (long k=0; k<imageW*imageH; k++){
        int i = k / imageW;
        int j = k % imageW;

        Ray ray(cam.eye, screenTopLeft + (pixelSize.pixelH*(i)) + 
            (pixelSize.pixelW*(j)) + (pixelSize.pixelMid), true);

        image[i][j] = shootRay(ray, 1).between();

        // progress counter
        #pragma omp critical
        if (++count % counttill == 0)
            cout<<"\rRendering "<<outfile<<": "<<(float)count/imageW*100/imageH<<"%"<<flush;
        
    }

    cout<<flush<<"\rRendering complete"<<flush<<endl;
}
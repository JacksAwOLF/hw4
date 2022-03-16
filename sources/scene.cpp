#include "Scene.h"
#include <omp.h>

Scene::Scene(){
    debug = false;
    maxdepth = 5;
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

        if (debug) objs[i]->debug = true;
        if (!objs[i]->intersectWithRay(ray, pp)){
            if (debug) objs[i]->debug = false;
            continue;
        }
        if (debug) objs[i]->debug = false;

        float tt = ray.getT(pp);

        // if (debug) cout<<"found obj with int at "<<pp<<" time "<<tt<<endl;

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

void Scene::render(){
    
    long count = 0, counttill = 100;
    
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
        Ray ray(cam.eye, screenTopLeft + (pixelSize.pixelH*(i)) + 
            (pixelSize.pixelW*(j)) + (pixelSize.pixelMid), true);

        // cout<<"hit1\n";
        Intersection hit = firstObjHit(ray);

        if (hit.obj != nullptr) {

            // image[i][j] = hit.pos.normalize();
            
            // #pragma omp critical
            // image[i][j] = (hit.obj->surfaceNormal(hit.pos) 
            //     + Arr3(1,1,1)).minmaxnorm();

            // cerr<<i<<" "<<j<<": "<<(hit.obj->surfaceNormal(hit.pos))<<endl;
            // // #pragma omp critical
            // // {
            // //     cout<<i<<" "<<j<<": first hit "<<hit.pos<<" with ray "<<ray<<endl;
            // //     //"... nor: "<<image[i][j]<<endl;
            // //     // cout<<"second hit "<<hit2.pos<<" with ray "<<ltRay<<endl;
            // //     // cout<<"tt: "<<ltRay.getT(hit2.pos)<<endl<<endl;
            // //     // debug = true;
            // //     // firstObjHit(ltRay);
            // //     // debug = false;
            // // }


            // continue;

            // cout<<k<<" hit1 sth\n";

            // material color
            // #pragma omp critical
            image[i][j].add(hit.obj->shadingVars.ambience + 
                (hit.obj->shadingVars.emission));

            // cout<<k<<" hit2 sth\n";

            // light shading color
            for (Light light : lights){
                // cout<<"lt1\n";

                Ray ltRay(hit.pos, light.position, !light.directional);

                // epsilon shift for shadow ray
                // ltRay.slope = ltRay.slope.normalize();
                // ltRay.start = ltRay.at(TOLERANCE);

                // cout<<"hit2\n";
                Intersection hit2 = firstObjHit(ltRay);
                // cout<<"lt2\n";

                bool toShade = // true;
                    hit2.obj == nullptr || 
                    (!light.directional && 
                        (hit2.pos-(hit.pos)).length() > 
                        (light.position-(hit.pos)).length());

                if (toShade){
                    // cout<<"lt2.5\n";
                    // #pragma omp critical
                    image[i][j].add(light.shade(hit, cam.eye));
                    // cout<<"lt2.8\n";
                }

                else {
                    
                    // #pragma omp critical
                    // {
                    //     cout<<endl<<"first hit "<<hit.pos<<" with ray "<<ray<<endl;
                    //     if (hit2.obj != nullptr)
                    //         cout<<"second hit "<<hit2.pos<<" with ray "<<ltRay<<endl;
                    //     cout<<"tt: "<<ltRay.getT(hit2.pos)<<endl;
                    //     debug = true;
                    //     firstObjHit(ltRay);
                    //     debug = false;
                    // }

                }
                // cout<<"lt3\n";


                // if (i == 10 && j == 8){
                //     cout<<"first intersection at "<<hit.pos<<" with ray "<<ray<<endl; 
                //     cout<<"ltray: "<<ltRay<<endl<<"hit point ";
                //     cout<<hit2.pos<<" t: "<<ltRay.getT(hit2.pos)<<endl;
                //     cout<<"image at this point "<<image[i][j]<<endl;
                // }
            }

            // if ((image[i][j] - Arr3(.1, .1, .9)).length() <= 0.3){
            //     cout<<i<<" "<<j<<": "<<image[i][j]<<endl;
            //     // cout<<"color "<<image[i][j]<<endl;
            //     // cout<<"first hit "<<hit.pos<<" with ray "<<ray<<endl;
            // }

            // cout<<image[i][j]<<endl;

            image[i][j].between(0.0, 1.0);


        }

        // progress counter
        #pragma omp critical
        if (++count % counttill == 0)
            cout<<"\rRendering "<<outfile<<": "<<(float)count/imageW*100/imageH<<"%"<<flush;
        
    }

    cout<<flush<<"\rRendering complete"<<flush<<endl;
}
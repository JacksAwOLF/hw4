#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ppm.h"
#include "scene.h"
#include "obj.h"
#include "readfile.h"
#include "color.h"
using namespace std;

// scene height and width in pixels
int w, h;

// the rays that shoot through each pixel
vector<Ray> rays;

V3 backgroundColor = V3(0.0, 0.0, 0.0);

int main(int argc, char* argv[]){

    if (argc == 1) {
        cerr<<"Include file to read\n";
        return -1;
    }

    int whichCam = 1;
    if (argc >= 4) {
        whichCam = (argv[3][0] - '0');
    }

    Scene scene;
    vector<VirtualObj*> objs;
    if (!readfile(argv[1], scene, objs, whichCam)) {
        cerr<<"Error reading file "<<argv[1]<<endl;
        return -1;
    }

    cout<<"finished reading file, # objs: "<<objs.size()<<endl;
    // for (int i=0; i<objs.size(); i++){
    //     cout<<i<<"th obj is a "<<((objs[i])->getName())<<endl;
    //     cout<<"and color is "<<(objs[i]->color).ambient<<endl;
    // }

    w = scene.w;
    h = scene.h;
    PPM image(w, h, 255, backgroundColor);
    rays = scene.getRays();

    // loop over all the rays
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {

            int ri = i*w+j;
            // cout<<"\nray "<<ri<<": "<<rays[ri].a<<"+t*"<<rays[ri].b<<endl;

            // loop over all objects to find where the closest intersection is
            image.set(i, j, backgroundColor);

            float t = -1;
            VirtualObj* obj;
            for (int k=0; k<objs.size(); k++) {
                float tt = objs[k]->intersectWithRay(rays[ri]);
                if (tt > 0 && (t == -1 || tt < t)) {
                    t = tt;
                    obj = objs[k];
                }
            }

            if (t == -1) continue;

            // cout<<"intersection: "<<t<<endl;
            V3 point = rays[ri].getPoint(t);
            image.set(i, j, obj->color.calculate(point));
            // cout<<"color: "<<obj->color.calculate(point)<<endl;
        }
    }

    image.write(argc>=3 ? argv[2] : "test.ppm");
    return 0;
}
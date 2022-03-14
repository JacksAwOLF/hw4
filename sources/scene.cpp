#include "scene.h"

Ray::Ray(V3 from, V3 to){
    a = from;
    b = to - from;
}

V3 Ray::getPoint(float t){
    return a + b * t;
}

void Scene::setCamera(istream& in) {
    in >> eye >> at >> up >> foy;
    dis = (at - eye);
    
    // hor = V3::normalize(up.cross(dis));
    hor = V3::normalize(dis.cross(up));

    ver = V3::normalize(dis.cross(hor));
    // ver = V3::normalize(hor.cross(dis));
}
void Scene::setScreen(istream& in) { in >> w >> h; }

vector<Ray> Scene::getRays() {
    vector<Ray> res;

    float theta = (foy/2) * 3.1415926535 / 180.0,
        screenH = sin(theta) / cos(theta) * dis.length() * 2,
        screenW = screenH * (w/h);
    V3  pixelH = ver * (screenH / h),
        pixelW = hor * (screenW / w),
        pixelMid = pixelH/2.0 + pixelW/2.0,
        botRight = at - (ver * screenH/2) - (hor * screenH/2 * (w/h)),
        curPos;

    cout<<"screen calc:\ntheta: "<<theta<<" screenH/W: "<<screenH<<" "<<screenW<<endl;
    cout<<"botR: "<<botRight<<" pixelW: "<<pixelW<<" pixelH: "<<pixelH<<endl;
    cout<<"camera: "<<eye<<" at: "<<at<<" dis: "<<dis<<" hor: "<<hor<<" ver: "<<ver<<endl;

    for (int i=0; i<h; i++) {
        curPos = botRight + pixelH * i;
        for (int j=0; j<w; j++) {
            V3 rr = curPos + pixelMid;
            // cout<<"rr: "<<rr<<endl;
            res.push_back(Ray(eye, rr));
            curPos = curPos + pixelW;
        }
    }

    return res;
}
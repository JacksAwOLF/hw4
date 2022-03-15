#include "Ray.h"

Ray::Ray(Arr3 a, Arr3 b, bool to){
    start = a;
    if (to) slope = b - a;
    else slope = b;
}

Arr3 Ray::at(float t){
    return start + slope * t;
}

float Ray::getT(Arr3 point){
    Arr3 p = point - start;
    // cout<<point<<" - "<<start<<" = "<<p<<endl;
    // cout<<p.length()<<" / "<<slope.length()<<endl;
    return p.length() / slope.length();
}

Ray Ray::transform(Mat4 mat){
    return Ray(mat * Arr4(start, 1), mat * Arr4(slope, 0), false);
}

ostream& operator<<(ostream& out, const Ray& r){
    return out<<r.start<<" + t * "<<r.slope;
}

// int main(){
//     Ray r = Ray(Arr3(0, 0, 4), Arr3(1, -1, 0));
//     Ray s = r.transform(Mat4::identity());
//     cout<<r<<endl;
//     cout<<s<<endl;
// }

// ray before: 0 0 4 + t * -0.357266 0 -4
// befbef: 0 0 4 + t * -0.357266 0 -4
// ray: 0 0 4 + t * -0.357266 0 -4
// intersect plane at -0.357266 0 0
// alpha beta: 0.678633 -0.178633

// outp: -0.357266 0 0 1

// befbef: 0 0 4 + t * -0.357266 0 -4
// ray: 0 0 4 + t * -0.357266 0 -4
// intersect plane at -0.357266 0 0
// alpha beta: 0.5 0.321367

// outp: -0.357266 0 0 1

// aftaft: 0 0 4 + t * -0.357266 0 -4
//          point -0.357266 0 -4 is not on ray 0 0 4 + t * -0.357266 0 -4
// ray after: 0 0 4 + t * -0.357266 0 -4
#include "Obj.h"

// constructors

Obj::Obj(ShadingVars svars, Transform tf){
    shadingVars = svars;
    transform = tf;
    debug = false;
    // cout<<"new obj with transform\n"<<tf.matrix<<" and inverse "<<tf.inverse<<endl;
}

bool Obj::intersectWithRay(Ray r, Arr3 &point) {
    return false;
}

void Obj::updateBBox(){}

bool Obj::touchBox(Ray ray){
    return box.intersectRay(ray.transform(transform.inverse));
}

Arr3 Obj::surfaceNormal(Arr3 point){
    return Arr3();
}

Triangle::Triangle(istream& in, vector<Arr3>& vertices, 
    ShadingVars svars, Transform tf): Obj(svars, tf){
    
    int ai, bi, ci; 
    in >> ai >> bi >> ci;
    a = vertices[ai];
    b = vertices[bi];
    c = vertices[ci];

    // precompute vars for intersection test
    aa = a - c;
    bb = b - c;
    n = aa.cross(bb).normalize();

    n_aa = aa.normalize();
    aap = aa.cross(n).normalize();
    bbDotaap = bb.dot(aap);
    bbDotn_aa = bb.dot(n_aa);

    updateBBox();

    // cout<<"triangle "<<a<<" , "<<b<<" , "<<c<<endl;
    // cout<<"aa: "<<aa<<" bb: "<<bb<<" normal: "<<n<<endl;
    // cout<<"triangle with transform: "<<tf.matrix<<tf.inverse;
}    

Sphere::Sphere(istream& in, 
    ShadingVars svars, Transform tf): Obj(svars, tf){
    
    in >> center >> radius;

    updateBBox();

    // cout<<"sphere with transform: "<<tf.matrix<<tf.inverse;
    // cout<<(Arr3)(tf.matrix * Arr4(center, 1))<<endl;
    // cout<<(tf.matrix.mult(tf.inverse))<<(tf.inverse.mult(tf.matrix))<<endl;
    // Ray r(Arr3(0,0,0), Arr3(0,0,1));
    // cout<<r<<endl;
    // cout<<r.transform(tf.inverse)<<endl;
    // cout<<r.transform(tf.inverse).transform(tf.matrix)<<endl;
    // cout<<r.transform(tf.inverse).transform(tf.matrix).transform(tf.inverse)<<endl;
}

// get surface normals
// note: point is in world view,
// we need to return normal in world view

Arr3 Triangle::surfaceNormal(Arr3 point){
    return transform.multNormal(n);
}

Arr3 Sphere::surfaceNormal(Arr3 point){
    Arr3 tfPoint = transform.inverse * Arr4 (point, 1);
    Arr3 modelN = tfPoint - center;
    return transform.multNormal(modelN);
}

// intersections

bool Triangle::intersectWithRay(Ray ray, Arr3 &point) {

    Ray tfray = ray.transform(transform.inverse);
    // Ray tfray = ray;

    // if ray is normal to plane, no intersection
    float den = tfray.slope.dot(n);
    if (den == 0.0){
        // cout<<"den is 0???\n";
        return false;
    }

    // find intersection point of ray and plane
    // Ray's equation: P = P0 + P1 * t
    // Plane equation: (P - A) dot n = 0,
    // where A is a point on plane and n is normal
    float t = (a.dot(n) - tfray.start.dot(n)) / den;
    Arr3 p = tfray.at(t);

    // pBug
    if (t < 0){ // dont count the shadow ray origin obj
        return false;
    }

    // check if point pp is in triangle
    // if it is within, then there exists alpha and beta
    // such that 0 <= alpha, beta <= 1 && alpha + beta <= 1
    Arr3 pp = p - c;
    
    // find bb and pp projection on aa'. the result of proj_pp / proj_bb is beta
    // find bb and pp projection on aa. alpha then is (proj_pp + proj_bb * beta) / |aa|
    float beta = pp.dot(aap) / bbDotaap;
    float alpha = (pp.dot(n_aa) - bbDotn_aa * beta) / aa.length();

    // cout<<endl;
    
    // if (debug){
    //     cout<<"tfray: "<<tfray.start<<" + t * "<<tfray.slope<<endl;
    //     cout<<"intersect plane at "<<p<<endl;
    //     cout<<"alpha beta: "<<alpha<<" "<<beta<<endl;
    //     cout<<"point: "<<transform.matrix * Arr4(p, 1)<<endl;
    //     // cout<<"point2: "<<ray.at(t)<<endl;
    // }

    // if (alpha < 0 || beta < 0 || alpha > 1 || beta > 1) 
        // return false;

    if (alpha < 0 || beta < 0 || alpha > 1 || beta > 1 || alpha + beta > 1) 
        return false;

    // if (debug) cout<<"             intersect!!!\n";

    point = transform.matrix * Arr4(p, 1);
    // point = ray.at(t);
    return true;
}  

bool Sphere::intersectWithRay(Ray ray, Arr3 &point) {

    Ray tfray = ray.transform(transform.inverse);

    // Ray's equation: P = P0 + P1 * t
    // Sphere's equation: <P - U> dot <P - U> = r^2
    // combine to get quadratic formula with variable t
    Arr3 delta = tfray.start - center;
    float a = tfray.slope.dot(tfray.slope),
        b = (tfray.slope * (float)2).dot(delta),
        c = (delta).dot(delta) - radius * radius;
    
    // check roots: if none (b < 4ac), no intersect
    // if same roots (b = 4ac), ray is perpendicular
    // if 2 roots, ray goes throuhg twice
    float check = b*b - 4*a*c;
    if (check < 0)
        return false;

    // only count the smallest positive intersection
    float t1 = (-b + sqrt(check)) / (2 * a),
        t2 = (-b - sqrt(check)) / (2 * a), t;
    if (t1 < 0 && t2 < 0) return false;
    if (t1 < 0) t = t2;
    else if (t2 < 0) t = t1;
    else t = min(t1, t2);

    // cout<<"point1 "<< transform.matrix * Arr4(tfray.at(t1), 1)
    //     <<" point2 "<<transform.matrix * Arr4(tfray.at(t2), 1)<<endl;
    // cout<<"ray "<<ray<<" transformed "<<tfray<<endl;
    // cout<<"modelp1 "<<tfray.at(t1)<<" modelp2 "<<tfray.at(t2)<<endl;

    point = transform.matrix * Arr4(tfray.at(t), 1);
    return true;
}

void Triangle::updateBBox(){
    for (int i=0; i<3; i++){
        box.mins[i] = min(min(a[i], b[i]), c[i]);
        box.maxs[i] = max(max(a[i], b[i]), c[i]);
    }
    // cout<<"my bounding box is "<<box.mins<<" and "<<box.maxs<<endl;
}

void Sphere::updateBBox(){
    for (int i=0; i<3; i++){
        box.mins[i] = center[i] - radius;
        box.maxs[i] = center[i] + radius;
    }
}
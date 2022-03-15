#include "Obj.h"

// constructors

Obj::Obj(ShadingVars svars, Transform tf){
    shadingVars = svars;
    transform = tf;
    // cout<<"new obj with transform\n"<<tf.matrix<<" and inverse "<<tf.inverse<<endl;
}

bool Obj::intersectWithRay(Ray r, Arr3 &point) {
    return false;
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

    // cout<<"triangle "<<a<<" , "<<b<<" , "<<c<<endl;
    // cout<<"aa: "<<aa<<" bb: "<<bb<<" normal: "<<n<<endl;
}    

Sphere::Sphere(istream& in, 
    ShadingVars svars, Transform tf): Obj(svars, tf){
    
    in >> center >> radius;

    cout<<"sphere with transform: "<<tf.matrix<<tf.inverse;
}

// get surface normals

Arr3 Triangle::surfaceNormal(Arr3 point){
    return n;
}

Arr3 Sphere::surfaceNormal(Arr3 point){
    return point - center;
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

    if (t == 0){ // dont count the shadow ray origin obj
        return false;
    }

    // check if point pp is in triangle
    // if it is within, then there exists alpha and beta
    // such that 0 <= alpha, beta <= 1 && alpha + beta <= 1
    Arr3 pp = p - c, 
        n_aa = aa.normalize(),
        aap = aa.cross(n).normalize();
    
    // find bb and pp projection on aa'. the result of proj_pp / proj_bb is beta
    // find bb and pp projection on aa. alpha then is (proj_pp + proj_bb * beta) / |aa|
    float beta = (pp.dot(aap)) / (bb.dot(aap));
    float alpha = ((pp.dot(n_aa)) - (bb.dot(n_aa)) * beta) / aa.length();

    // cout<<endl;
    // cout<<"transform of obj is "<<transform.inverse<<endl;
    // cout<<"ray: "<<tfray.start<<" + t * "<<tfray.slope<<endl;
    // cout<<"                 intersect plane at "<<p<<endl;
    // cout<<"alpha beta: "<<alpha<<" "<<beta<<endl;
    // cout<<"outp: "<<transform.matrix * Arr4(p, 0)<<endl;

    // if (alpha < 0 || beta < 0 || alpha > 1 || beta > 1) 
        // return false;

    if (alpha < 0 || beta < 0 || alpha > 1 || beta > 1 || alpha + beta > 1) 
        return false;

    // cout<<"             intersect!!!\n";
    point = transform.matrix * Arr4(p, 1);
    // point = ray.at(t);
    return true;
}  

bool Sphere::intersectWithRay(Ray ray, Arr3 &point) {

    Ray tfray = ray.transform(transform.inverse);

    // Ray's equation: P = P0 + P1 * t
    // Sphere's equation: <P - U> dot <P - U> = r^2
    // combine to get quadratic formula with variable t
    float a = tfray.slope.dot(tfray.slope),
        b = (tfray.slope * (float)2).dot(tfray.start - center),
        c = (tfray.start - center).dot(tfray.start - center) - radius * radius;
    
    // check roots: if none (b < 4ac), no intersect
    // if same roots (b = 4ac), ray is perpendicular
    // if 2 roots, ray goes throuhg twice
    float check = b*b - 4*a*c;
    if (check < 0)
        return false;

    // only count the smallest positive intersection
    float t1 = (-b + sqrt(check)) / (2 * a),
        t2 = (-b - sqrt(check)) / (2 * a);
    if (t1 < 0 && t2 < 0) return false;
    if (t1 < 0) point = tfray.at(t2);
    else if (t2 < 0) point = tfray.at(t1);
    else point = tfray.at(min(t1, t2));

    // cout<<"ray "<<ray<<" transformed "<<tfray<<endl;
    // cout<<"int point "<<point<<" transformed ";
    point = transform.matrix * Arr4(point, 0);
    // cout<<point<<endl;
    return true;
}
    
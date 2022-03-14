#include "Obj.h"

// constructors

Obj::Obj(ShadingVars svars, Transform tf){
    shadingVars = svars;
    transform = tf;
}

float Obj::intersectWithRay(Ray r){
    return -1;
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
}    

Sphere::Sphere(istream& in, 
    ShadingVars svars, Transform tf): Obj(svars, tf){
    
    in >> center >> radius;
}

// get surface normals

Arr3 Triangle::surfaceNormal(Arr3 point){
    return n;
}

Arr3 Sphere::surfaceNormal(Arr3 point){
    return point - center;
}

// intersections

float Triangle::intersectWithRay(Ray ray) {

    // if ray is normal to plane, no intersection
    float den = ray.slope.dot(n);
    if (den == 0.0)
        return -1;

    // find intersection point of ray and plane
    // Ray's equation: P = P0 + P1 * t
    // Plane equation: (P - A) dot n = 0,
    // where A is a point on plane and n is normal
    float t = (a.dot(n) - ray.start.dot(n)) / den;
    Arr3 p = ray.start + ray.slope * t;

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
    if (alpha < 0 || beta < 0 || alpha > 1 || beta > 1 || alpha + beta > 1) 
        return -1;

    return t;
}  

float Sphere::intersectWithRay(Ray ray) {

    // Ray's equation: P = P0 + P1 * t
    // Sphere's equation: <P - U> dot <P - U> = r^2
    // combine to get quadratic formula with variable t
    float a = ray.slope.dot(ray.slope),
        b = (ray.slope * (float)2).dot(ray.start - center),
        c = (ray.start - center).dot(ray.start - center) - radius * radius;
    
    // check roots: if none (b < 4ac), no intersect
    // if same roots (b = 4ac), ray is perpendicular
    // if 2 roots, ray goes throuhg twice
    float check = b*b - 4*a*c;
    if (check < 0)
        return -1;

    // only count the smallest positive intersection
    float t1 = (-b + sqrt(check)) / (2 * a),
        t2 = (-b - sqrt(check)) / (2 * a);
    if (t1 < 0 && t2 < 0) return -1;
    if (t1 < 0) return t2;
    if (t2 < 0) return t1;
    return min(t1, t2);
}
    
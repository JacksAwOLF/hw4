#include "obj.h"

string VirtualObj::getName() {return "VirtualObj";}
string Triangle::getName() {return "Triangle";}
string Sphere::getName() {return "Sphere";}


Triangle::Triangle(istream& in, vector<V3>& vertices, 
    Color clr, Transform tf) {

    int ai, bi, ci; in>>ai>>bi>>ci;
    a = vertices[ai].copy();
    b = vertices[bi].copy();
    c = vertices[ci].copy();

    // calculate normal of the triangle
    aa = a - c;
    bb = b - c;
    n = V3::normalize(aa.cross(bb));

    color = clr.copy();
    //TODO: instead of transforming the ray, can i just 
    // transform this object? yes but ellipse?
    // transform = tf.copy();
    cout<<"transformatoin is: "<<tf<<endl;
    cout<<"before multiply: "<<a<<" , "<<b<<" , "<<c<<endl;
    a = tf.multPoint(a);
    b = tf.multPoint(b);
    c = tf.multPoint(c);
    cout<<"after multiply: "<<a<<" , "<<b<<" , "<<c<<endl;
    aa = a - c;
    bb = b - c;
    n = V3::normalize(aa.cross(bb));
}  

Sphere::Sphere(istream& in, Color clr, Transform tf) { 
    in >> center >> r; 

    color = clr.copy();
    //TODO: instead of transforming the ray, can i just 
    // transform this object? no. ellipse?
    // transform = tf.copy();
}


float VirtualObj::intersectWithRay(Ray ray) {
    return -1;
}

float Triangle::intersectWithRay(Ray ray) {
    // cout<<endl<<endl;

    // if ray is normal to plane, no intersection
    float den = ray.b * n;
    if (den == 0.0){
        // cout<<"den is 0?\n";
        return -1;     // pBUG: tolerate error?
    }

    // find intersection point of ray and plane
    // Ray's equation: P = P0 + P1 * t
    // Plane equation: (P - A) dot n = 0,
    // where A is a point on plane and n is normal
    float t = (a * n - ray.a * n) / den;
    V3 p = ray.a + ray.b * t;

    // cout<<"triangle: ray from "<<ray.a<<" slope "<<ray.b<<endl;
    // cout<<"normal of plane: "<<n<<endl;
    // cout<<"intersect with plane at "<<p<<endl;

    V3 pp = p - c;
    // check if point pp is in triangle
    // if it is within, then there exists alpha and beta
    // such that 0 <= alpha, beta <= 1 && alpha + beta <= 1

    // (at this point pp, aa, bb are all on the same plane so we can think 2d)
    // (we can also guarantee that aa and bb aren't parallel since they are edges in triangle)

    // TODO: a lot of this can be in creation process

    // construct another axis off aa that is perpendicular aa'
    // aa' = cross(aa, cross(aa, bb))
    V3 n_aa = V3::normalize(aa),
        aap = V3::normalize(aa.cross(n));

    // find bb and pp projection on aa'. the result of proj_pp / proj_bb is beta
    float ppPaap = pp * aap, bbPaap = bb * aap; // don't have to divide by |aap| since it's 1
    float beta = ppPaap / bbPaap;

    // find bb and pp projection on aa. alpha then is (proj_pp + proj_bb * beta) / |aa|
    
    float ppPaa = pp * n_aa, bbPaa = bb * n_aa;
    float alpha = (ppPaa - bbPaa * beta) / aa.length();

    if (alpha < 0 || beta < 0 || alpha > 1 || beta > 1 || alpha + beta > 1) {
        return -1;
    }

    return t;
}

float Sphere::intersectWithRay(Ray ray) {

    // Ray's equation: P = P0 + P1 * t
    // Sphere's equation: <P - U> dot <P - U> = r^2
    // combine to get quadratic formula with variable t
    float a = ray.b * ray.b,
        b = ray.b * (float)2 * (ray.a - center),
        c = (ray.a - center) * (ray.a - center) - r * r;

    // check roots: if none (b < 4ac), no intersect
    // if same roots (b = 4ac), ray is perpendicular
    // if 2 roots, ray goes throuhg twice
    float check = b*b - 4*a*c;
    // cout<<"sphere: ray "<<ray.a<<" "<<ray.b<<endl;
    // cout<<"result "<<a<<" "<<b<<" "<<c<<endl;
    // cout<<check<<endl;
    if (check < 0) return -1;

    // only count the smallest positive intersection
    float t1 = (-b + sqrt(check)) / (2 * a),
        t2 = (-b - sqrt(check)) / (2 * a);
    if (t1 < 0 && t2 < 0) return -1;
    if (t1 < 0) return t2;
    if (t2 < 0) return t1;
    return min(t1, t2);
}

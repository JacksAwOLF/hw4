#include "v3.h"
#include <math.h>
using namespace std;

// constructors
V3::V3() { V3(0.0, 0.0, 0.0); }
V3::V3(istream& in) { in >> x >> y >> z; }
V3::V3(float xx, float yy, float zz):
    x(xx), y(yy), z(zz) {}

// some helping functions
V3 V3::copy() { return V3(x, y, z); }
float V3::length() { return sqrt(x*x + y*y + z*z); }
V3 V3::normalize(V3 v) { return v / v.length(); }
V3 V3::getRound() { return V3(round(x), round(y), round(z)); }

// add/sub vector with vector elementwise
V3 V3::operator+(const V3& o) { return V3(x+o.x, y+o.y, z+o.z); }
V3 V3::operator-(const V3& o) { return V3(x-o.x, y-o.y, z-o.z); }

// dot/cross product
float V3::operator*(const V3& o) { return x*o.x + y*o.y + z*o.z; }
V3 V3::cross(const V3& o) {
    return V3(y*o.z-z*o.y, z*o.x-x*o.z, x*o.y-y*o.x);
}

// multiply/divide vector with constant
V3 V3::operator*(const float& o) { return V3(x*o, y*o, z*o); }
V3 V3::operator/(const float& o) { return V3(x/o, y/o, z/o); }

// easy input/output
istream& operator>>(istream& is, V3& V) {
    is >> V.x >> V.y >> V.z;
    return is;
}

ostream& operator<<(ostream& os, const V3& V) {
    os<<V.x<<" "<<V.y<<" "<< V.z;
    return os;
}
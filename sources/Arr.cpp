#include "Arr.h"

// constructors

Arr::Arr(){}
Arr3::Arr3(): Arr(3) {}
Arr4::Arr4(): Arr(4) {}
Arr::Arr(const Arr& o){
    int n = size();
    if (n == 0 && o.size() != 0){   
        for (int i=0; i<o.size(); i++)
            data.push_back(o[i]);
    } else {
        for (int i=0; i<n; i++)
            data[i] = 0;
        for (int i=0; i<n && i<o.size(); i++)
            data[i] = o[i];
    }
}

Arr::Arr(int size){
    for (int i=0; i<size; i++)
        data.push_back(0);
}

Arr::Arr(int size, istream& in){
    for (int i=0; i<size; i++){
        float x; in>>x;
        data.push_back(x);
    }
}

Arr3::Arr3(Arr arr){
    for (int i=0; i<3; i++)
        data.push_back(arr[i]);
}

Arr4::Arr4(Arr arr){
    for (int i=0; i<4; i++)
        data.push_back(arr[i]);
}

Arr3::Arr3(istream& is): Arr(3, is){}
Arr4::Arr4(istream& is): Arr(4, is){}

Arr3::Arr3(float a, float b, float c){
    data.push_back(a);
    data.push_back(b);
    data.push_back(c);
}

Arr4::Arr4(float a, float b, float c, float d){
    data.push_back(a);
    data.push_back(b);
    data.push_back(c);
    data.push_back(d);
}
Arr4::Arr4(Arr3 arr, float x){
    for (int i=0; i<arr.size(); i++)
        data.push_back(arr[i]);
    data.push_back(x);
}

// common helping functions

Arr Arr::negative(){
    Arr res(size());
    for (int i=0; i<size(); i++)
        res[i] = -data[i];
    return res;
}

Arr Arr::minmaxnorm(){
    if (size()>1){
        float mn=data[0], mx=data[0];
        for (int i=0; i<size(); i++){
            mn = min(mn, data[i]);
            mx = max(mx, data[i]);
        }
        if (mn != mx){
            for (int i=0; i<size(); i++)
                data[i] = (data[i]-mn) / (mx-mn);
        } else {
            return between();
        }
    }
    return *this;
}

Arr Arr::between(float small, float large){
    for (int i=0; i<size(); i++){
        if (data[i] < small) data[i] = small;
        if (data[i] > large) data[i] = large;
    }
    return *this;
}

Arr Arr::copy(){
    Arr res(size());
    for (int i=0; i<size(); i++)
        res[i] = data[i];
    return res;
}

int Arr::size() const{
    return data.size();
}

float Arr::length(){
    float res = 0;
    for (int i=0; i<size(); i++)
        res += data[i] * data[i];
    return sqrt(res);
}

void Arr::checkSize(const Arr& o){
    if (size() != o.size()){
        // TODO: exception handling
        cerr<<"wrong size\n";
    }
}

Arr Arr::normalize(){
    // Arr res = copy();
    return *this / length();
}

Arr4 Arr4::dehomogenize(){
    if (data[3] == 0){
        cerr<<"Cannot dehomogenize when w is 0\n";
        return *this;
    }
    return *this / data[3];
}

float Arr::operator[](int i) const {
    return data[i];
}

float& Arr::operator[](int i) {
    return (data[i]);
}

// elementwise operations with other Arr

Arr Arr::operator+(const Arr &o){
    checkSize(o);
    Arr res(size());
    for (int i=0; i<size(); i++)
        res[i] = data[i] + o[i];
    return res;
}

Arr Arr::operator-(const Arr &o){
    checkSize(o);
    Arr res(size());
    for (int i=0; i<size(); i++)
        res[i] = data[i] - o[i];
    return res;
}

Arr Arr::operator*(const Arr &o){
    checkSize(o);
    Arr res(size());
    for (int i=0; i<size(); i++)
        res[i] = data[i] * o[i];
    return res;
}

Arr Arr::add(const Arr& o){
    for (int i=0; i<size(); i++)
        data[i] += o[i];
    return *this;
}
Arr Arr::sub(const Arr& o){
    for (int i=0; i<size(); i++)
        data[i] -= o[i];
    return *this;
}
Arr Arr::mul(const Arr& o){
    for (int i=0; i<size(); i++)
        data[i] *= o[i];
    return *this;
}

// scaling with a scalar

Arr Arr::operator*(const float &o){
    Arr res(size());
    for (int i=0; i<size(); i++)
        res[i] = data[i] * o;
    return res;
}

Arr Arr::mul(const float &o){
    for (int i=0; i<size(); i++)
        data[i] *= o;
    return *this;
}

Arr Arr::div(const float &o){
    for (int i=0; i<size(); i++)
        data[i] /= o;
    return *this;
}

Arr Arr::operator/(const float &o){
    Arr res(size());
    for (int i=0; i<size(); i++)
        res[i] = data[i] / o;
    return res;
}

// dot product and cross product

float Arr::dot(const Arr &o){
    float res = 0;
    for (int i=0; i<size(); i++)
        res += data[i] * o[i];
    return res;
}

Arr3 Arr3::cross(Arr3 o){
    return Arr3(
        data[1]*o[2] - data[2]*o[1],
        data[2]*o[0] - data[0]*o[2],
        data[0]*o[1] - data[1]*o[0]
    );
}

Arr Arr::round(){
    for (int i=0; i<size(); i++)
        data[i] = std::round(data[i]);
    return *this;
}

// input/output

istream& operator>>(istream& is, Arr& arr){
    for (int i=0; i<arr.size(); i++)
        is >> arr[i];
    return is;
}
istream& operator>>(istream& is, Arr3& arr){
    return is >> (Arr&) arr;
}
istream& operator>>(istream& is, Arr4& arr){
    return is >> (Arr&) arr;
}

ostream& operator<<(ostream& os, const Arr& arr){
    for (int i=0; i<arr.size(); i++){
        os << (arr[i]);
        if (i+1 != arr.size())
            os << ' ';
    }
    return os;
}
ostream& operator<<(ostream &os, const Arr3 &arr){
    return os << (Arr&) arr;
}
ostream& operator<<(ostream& os, const Arr4& arr){
    return os << (Arr&) arr;
}

// int main(){
//     Arr3 a(1, 2, 3);
//     cout<<a.minmaxnorm()<<endl;
// }
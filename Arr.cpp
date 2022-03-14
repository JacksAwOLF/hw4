#include "Arr.h"

// constructors

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

// is this right?
Arr3::Arr3(): Arr(3) {}
Arr4::Arr4(): Arr(4) {}

// common helping functions

int Arr::size() const{
    return data.size();
}

float Arr::length(){
    float res = 0;
    for (int i=0; i<size(); i++)
        res += data[i] * data[i];
    return sqrt(res);
}

void Arr::checkSize(Arr& o){
    if (size() != o.size()){
        // TODO: exception handling
        cerr<<"wrong size\n";
    }
}

Arr Arr::normalize(){
    return this / length;
}

float Arr::operator[](int i) const {
    return data[i];
}

float& Arr::operator[](int i) {
    return (data[i]);
}

// elementwise operations with other Arr

Arr Arr::operator+(Arr &o){
    checkSize(o);
    Arr res(size());
    for (int i=0; i<size(); i++)
        res[i] = data[i] + o[i];
    return res;
}

Arr Arr::operator-(Arr &o){
    checkSize(o);
    Arr res(size());
    for (int i=0; i<size(); i++)
        res[i] = data[i] - o[i];
    return res;
}

// scaling with a scalar

Arr Arr::operator*(const float &o){
    Arr res(size());
    for (int i=0; i<size(); i++)
        res[i] = data[i] * o;
    return res;
}

Arr Arr::operator/(const float &o){
    Arr res(size());
    for (int i=0; i<size(); i++)
        res[i] = data[i] / o;
    return res;
}

// dot product and cross product

float Arr::operator*(Arr &o){
    float res = 0;
    for (int i=0; i<size(); i++)
        res += data[i] * o[i];
    return res;
}

Arr Arr::cross(Arr o){
    if (size() != 3 || o.size() != 3){
        // TODO: exception
        cerr<<"can't cross product with non size3"<<endl;
    }
    return Arr3(
        data[1]*o[2] - data[2]*o[1],
        data[2]*o[0] - data[0]*o[2],
        data[0]*o[1] - data[1]*o[0]
    );
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
ostream& operator<<(ostream& os, Arr4& arr){
    return os << (Arr&) arr;
}

Arr3::Arr3(istream& is): Arr(3, is){}
Arr3::Arr3(float a, float b, float c){
    data.push_back(a);
    data.push_back(b);
    data.push_back(c);
}

Arr4::Arr4(istream& is): Arr(4, is){}
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

int main(){
    Arr3 a(cin);
    Arr3 b(1, 2, 3);
    cout<<"a is "<<a*2<<endl;
    cout<<"b is "<<b<<endl;
    cout<<"a*b is "<<((a * 2).cross(b))<<endl;
    return 0;
}
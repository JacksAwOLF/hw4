#include "Arr.h"

// constructors

Arr::Arr(){}
Arr3::Arr3(): Arr(3) {}
Arr4::Arr4(): Arr(4) {}

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
    return *this / length();
}

Arr4 Arr4::dehomogenize(){
    if (data[3] == 0){
        cerr<<"Cannot dehomogenize when w is 0\n";
        return nullptr;
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

Arr3 Arr3::cross(Arr3 o){
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

// int main(){
//     Arr aa(2);
//     aa[0] = 2; aa[1] = 1;
//     Arr bb(2);
//     bb[0] = 9; bb[1] = 11;
//     Arr3 a(2, 3, 1);
//     Arr3 b(1, 2, 3);
//     Arr3 c = a + b;
//     float cc = aa * bb;
//     cout<<"a is "<<a.normalize()<<endl;
//     cout<<"b is "<<b<<endl;
//     cout<<"c is "<<c<<endl;
//     cout<<"cc "<<cc<<endl;
//     cout<<"a cross b is "<<(((Arr3)(a * 2)).cross(b))<<endl;
//     return 0;
// }
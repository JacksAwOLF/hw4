#include "Intersection.h"

Intersection::Intersection(){
    obj = nullptr;
}

Intersection::Intersection(Obj* obj, Arr3 pos, Arr3 nor){
    this->obj = obj;
    this->pos = pos;
    this->nor = nor;
}
#include "Intersection.h"

Intersection::Intersection(){
    obj = nullptr;
}

Intersection::Intersection(Obj* obj, Arr3 pos){
    this->obj = obj;
    this->pos = pos;
}
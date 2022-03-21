#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Arr.h"
#include "Obj.h"

// a simple class, because I don't wanna use pair<>
class Intersection{
public:
    Obj* obj;
    Arr3 pos, nor;
    Intersection();
    Intersection(Obj* obj, Arr3 pos, Arr3 nor);
};

#endif
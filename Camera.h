#ifndef CAMERA_H
#define CAMERA_H

#include "Arr.h"
#include <iostream>
using namespace std;

// just a simple class to store things better
class PixelSize{
    Arr3 pixelW, pixelH, pixelMid;
    PixelSize(Arr3 w, Arr3 h);
};

class Camera{
private:
    Arr3 eye, at, up;
    float foy;

public:
    Camera(istream&);

    // return the pixelH and pixelW
    PixelSize calculatePixelSize(int w, int h);
};

#endif
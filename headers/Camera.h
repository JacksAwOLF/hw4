#ifndef CAMERA_H
#define CAMERA_H

#include "Arr.h"
#include <cmath>

// just a simple class to store things better
class PixelSize{
public:
    Arr3 pixelW, pixelH, pixelMid;
    PixelSize();
    PixelSize(Arr3 w, Arr3 h);
};

class Camera{
private:
public:
    Arr3 eye, at, up;
    float foy;
    
    Camera();
    Camera(istream&);

    // return the pixelH and pixelW
    PixelSize calculatePixelSize(int w, int h);
};

#endif
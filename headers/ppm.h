#ifndef PPM_H
#define PPM_H

#include <vector>
#include "v3.h"

class PPM {
private:
    vector< vector<V3> > image;
    int w, h, maxVal;

public:
    PPM(int w, int h, int maxVal=255, V3 initVal=V3(0.0,0.0,0.0));
    void clear(V3 val);
    bool set(int r, int c, V3 val);
    bool write(const char* filename);
};

#endif
#include "ppm.h"
#include <fstream>
#include <math.h>

PPM::PPM(int w, int h, int maxVal, V3 initVal):
    w(w), h(h), maxVal(maxVal){
        clear(initVal);
    }

void PPM::clear(V3 val) {
    for (int i=0; i<image.size(); i++)
        image[i].clear();
    image.clear();

    for (int i=0; i<h; i++) {
        vector<V3> line;
        for (int j=0; j<w; j++)
            line.push_back(val.copy());
       image.push_back(line);
    }
}

bool PPM::set(int r, int c, V3 val) {
    if (r >= image.size() || c >= image[r].size())
        return false;
    image[r][c] = val.copy();
    return true;
}

bool PPM::write(const char* filename) {
    ofstream out;
    out.open(filename);
    if (!out.is_open())
        return false;
    out << "P3\n" << w << " " << h;
    out << endl << maxVal << endl;
    for (int i=0; i<h; i++)
        for (int j=0; j<w; j++)
            out << (image[i][j]*maxVal).getRound() << endl;
    out.close();
    return true;
}
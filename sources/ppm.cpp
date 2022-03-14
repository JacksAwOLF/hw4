#include "Scene.h"
#include <fstream>
using namespace std;

const int maxPPMVal = 255;

bool ppmFromScene(const char* filename, Scene scene) {
    ofstream out;
    out.open(filename);
    if (!out.is_open())
        return false;
    out << "P3\n" << scene.w << " " << scene.h;
    out << endl << maxPPMVal << endl;
    for (int i=0; i<h; i++)
        for (int j=0; j<w; j++)
            out << (scene.image[i][j]*maxVal).round() << endl;
    out.close();
    return true;
}
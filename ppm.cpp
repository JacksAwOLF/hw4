#include "Scene.h"
#include <fstream>
using namespace std;

const int maxPPMVal = 255;

bool ppmFromScene(const char* filename, Scene scene) {
    ofstream out;
    out.open(filename);
    if (!out.is_open())
        return false;
    out << "P3\n" << scene.imageW << " " << scene.imageH;
    out << endl << maxPPMVal << endl;
    for (int i=0; i<scene.imageH; i++)
        for (int j=0; j<scene.imageW; j++)
            out << (scene.image[i][j]*maxPPMVal).round() << endl;
    out.close();
    return true;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Scene.h"
#include "readfile.cpp"
#include "ppm.cpp"
using namespace std;

int main(int argc, char* argv[]){

    if (argc == 1) {
        cerr<<"Include file to read\n";
        return -1;
    }

    int whichCam = 1;
    if (argc >= 4) {
        whichCam = (argv[3][0] - '0');
    }

    Scene scene = readfile(argv[1], whichCam);
    scene.render();

    if (!ppmFromScene(argc>=3 ? argv[2] : "test.ppm", scene)){
        cerr<<"Error converting to PPM Image\n";
        return -1;
    }
    
    return 0;
}
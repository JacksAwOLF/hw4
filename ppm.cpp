#include "Scene.h"
#include <fstream>
#include "lodepng.h"
using namespace std;

// const int maxPPMVal = 255;

bool ppmFromScene(Scene scene) {

    // lodepng::encode(filename, image, width, height);
    vector<unsigned char> img;
    for (int i=0; i<scene.imageH; i++)
        for (int j=0; j<scene.imageW; j++){
            scene.image[i][j].mul(255).round();
            for (int k=0; k<3; k++)
                img.push_back(scene.image[i][j][k]);
            img.push_back(255);
            // if (scene.image[i][j].length() != 0)
                // cerr<<i<<" "<<j<<": "<<scene.image[i][j]<<endl;
            // cout<<"got "<<a<<" for "<<i<<" "<<j<<endl;
        }

    // cout<<"writing to "<<scene.outfile<<endl;
    unsigned error = lodepng::encode(scene.outfile, img, scene.imageW, scene.imageH);

    if (error) cout<<"error: "<<lodepng_error_text(error)<<endl;

    // ofstream out;
    // out.open(scene.outfile+".ppm");
    // if (!out.is_open())
    //     return false;
    // out << "P3\n" << scene.imageW << " " << scene.imageH;
    // out << endl << maxPPMVal << endl;
    // for (int i=0; i<scene.imageH; i++)
    //     for (int j=0; j<scene.imageW; j++)
    //         out << (scene.image[i][j]*maxPPMVal).round() << endl;
    // out.close();
    return true;
}
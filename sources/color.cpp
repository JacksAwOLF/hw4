#include "color.h"

Color::Color(){
    // default values
    ambient = V3(0.2, 0.2, 0.2);
    emission = V3(0.0, 0.0, 0.0);
}

// Color::Color(V3 amb){
//     ambient = amb.copy();
// }

Color Color::copy() {
    Color ret;
    ret.ambient = ambient.copy();
    ret.emission = emission.copy();
    return ret;
}

V3 Color::calculate(V3 point) {
    V3 res = ambient + emission;

    

    return res;
}
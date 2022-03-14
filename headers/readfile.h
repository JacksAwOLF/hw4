#ifndef READFILE_H
#define READFILE_H

#include <fstream>
#include <sstream>
#include <vector>
#include "scene.h"
#include "obj.h"
#include "color.h"
#include "transform.h"

bool partOfString(char c, string s);
string removeSpaces(string s);
bool readfile(
    const char* filename,
    Scene& scene,
    vector<VirtualObj*>& objs,
    int whichCam);

#endif
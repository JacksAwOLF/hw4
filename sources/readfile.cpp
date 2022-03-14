#include "readfile.h"
using namespace std;

// helper function: checks if c is in s
bool partOfString(char c, string s) {
    for (int i=0; i<s.length(); i++)
        if (c == s[i])
            return true;
    return false;
}

// helper function: removes tabs/newlines from string
string removeSpaces(string s) {
    string res;
    for (int i=0; i<s.size(); i++)
        if (!partOfString(s[i], "\n\t\r"))
            res += s[i];
    return res;
}

bool readfile(const char* filename, Scene& scene,
    vector<VirtualObj*>& objs, int whichCam) {

    // opening the file to read
    ifstream in;
    in.open(filename);
    if (!in.is_open())
        return false;

    // camera things
    int countCam = 0;
    
    // color things
    Color color;

    // transform things
    vector<Transform> tfStack;
    tfStack.push_back(Transform::identity());
    Transform &curtf = tfStack[tfStack.size()-1];

    // read file in line by line
    string line;
    vector<V3> vertices;
    while (getline(in, line)) {

        // skip blank lines and comments
        line = removeSpaces(line);
        if (line == "" || line[0] == '#')
            continue;

        // create string stream and process commands
        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "size") scene.setScreen(ss);
        else if (cmd == "camera") {
            countCam += 1;
            if (countCam == whichCam)
                scene.setCamera(ss);
        }

        // creating objects
        else if (cmd == "maxverts") continue;
        else if (cmd == "vertex")
            vertices.push_back(V3(ss));
        else if (cmd == "tri")
            objs.push_back(new Triangle(ss, vertices, color, curtf));
        else if (cmd == "sphere")
            objs.push_back(new Sphere(ss, color, curtf));

        // specifying shading and coloring
        else if (cmd == "ambient") ss >> color.ambient;
        else if (cmd == "diffuse") ss >> color.diffuse;
        else if (cmd == "specular") ss >> color.specular;
        else if (cmd == "shininess") ss >> color.shininess;
        else if (cmd == "emission") ss >> color.emission;

        // specifying the transformations
        else if (cmd == "translate") 
            curtf.multiply(Transform::readInTranslate(ss));
        else if (cmd == "rotate") 
            curtf.multiply(Transform::readInRotate(ss));
        else if (cmd == "scale") 
            curtf.multiply(Transform::readInScale(ss));
        
        // push/pop Transform
        else if (cmd == "pushTransform"){
            tfStack.push_back(curtf.copy());
            curtf = tfStack[tfStack.size()-1];
        }
        else if (cmd == "popTransform"){
            if (tfStack.size() == 1){
                cerr<<"can't pop when transformStack is empty\n";
                continue;
            }
            tfStack.pop_back();
            curtf = tfStack[tfStack.size()-1];
        }


        else cerr<<"unrecognized command: "<<cmd<<endl;
    }

    return true;
}
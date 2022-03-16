#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include "Arr.h"
#include "Scene.h"
#include "ShadingVars.h"
#include "Transform.h"
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

// returns a Scene object from a file
Scene readfile(const char* filename, int whichCam=1){
    
    Scene scene;

    // opening the file to read
    ifstream in;
    in.open(filename);
    if (!in.is_open()){
        cerr<<"Error opening file\n";
        return scene;
    }

    int countCam = 0;

    ShadingVars svar;

    stack<Transform> tfStack;
    tfStack.push(Transform::identity());

    // read file in line by line
    string line;
    vector<Arr3> vertices;
    while (getline(in, line)) {
        
        // skip blank lines and comments
        line = removeSpaces(line);
        if (line == "" || line[0] == '#')
            continue;

        // create string stream and process commands
        stringstream ss(line);
        string cmd;
        ss >> cmd;

        // cout<<"begin line: "<<cmd<<endl;

        // basic commands
        if (cmd == "size") scene.setImage(ss);
        else if (cmd == "maxdepth") ss >> scene.maxDepth;
        else if (cmd == "output") ss >> scene.outfile;
        else if (cmd == "camera") {
            countCam += 1;
            if (countCam == whichCam)
                scene.setCamera(ss);
        }

        // creating objects
        else if (cmd == "maxverts") continue;
        else if (cmd == "vertex")
            vertices.push_back(Arr3(ss));
        else if (cmd == "tri")
            scene.objs.push_back(
                new Triangle(ss, vertices, svar, tfStack.top()));
        else if (cmd == "sphere")
            scene.objs.push_back(
                new Sphere(ss, svar, tfStack.top()));
    
        // TODO!!! vertnorms and trinorms

        // specifying the transformations

        // TODO: I thought i should multiply it the other way around?
        // right side gets evaluated first right?
        else if (cmd == "translate"){
            Transform t = Transform::inTranslate(ss);
            // cout<<"translate\n";
            // tfStack.top() = Transform::inTranslate(ss) * tfStack.top();
            tfStack.top() =  tfStack.top() * t;
            // cout<<"translate done\n";
        }
        else if (cmd == "rotate") {
            Transform t = Transform::inRotate(ss);
            tfStack.top() = tfStack.top() * t;
            // cout<<"rotation: "<<t.matrix<<"top of stack"<<tfStack.top().matrix<<endl;
            // tfStack.top() = t * tfStack.top();
            
        }
        else if (cmd == "scale"){
            // tfStack.top() = Transform::inScale(ss) * tfStack.top();
            Transform t = Transform::inScale(ss);
            tfStack.top() = tfStack.top() * t;
        }
        
        // push/pop Transform
        else if (cmd == "pushTransform"){
            tfStack.push(Transform(
                tfStack.top().matrix, tfStack.top().inverse));
            // cout<<"pushed\n"<<tfStack.top().matrix<<endl;
            // cout<<"size "<<tfStack.size()<<endl;
        }
        else if (cmd == "popTransform"){
            if (tfStack.size() == 1){
                cerr<<"can't pop when transformStack is empty\n";
                continue;
            }
            tfStack.pop();

            // cout<<"popped\n"<<tfStack.top().matrix<<endl;
            // cout<<"size "<<tfStack.size()<<endl;
        }

        // lighting
        else if (cmd == "directional") scene.addLight(ss, true);
        else if (cmd == "point") scene.addLight(ss, false);
        else if (cmd == "attenuation") ss >> scene.attenuation;

        // material
        else if (cmd == "diffuse") ss >> svar.diffuse;
        else if (cmd == "specular") ss >> svar.specular;
        else if (cmd == "shininess") ss >> svar.shininess;
        else if (cmd == "emission") ss >> svar.emission;   
        // yea in this assignment this is an per object variable
        else if (cmd == "ambient") ss >> svar.ambience; 


        else cerr<<"unrecognized command: "<<cmd<<endl;

        // cout<<"end of line\n";
    }


    return scene;
}
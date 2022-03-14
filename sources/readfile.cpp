#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
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
bool readfile(const char* filename, int whichCam=1){
    
    // opening the file to read
    ifstream in;
    in.open(filename);
    if (!in.is_open())
        return false;

    Scene scene;

    // color things
    ShadingVar svar;

    // transform things
    stack<Transform> tfStack;
    tfStack.push(Transform::identity());
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

        // basic commands
        if (cmd == "size") scene.
        else if (cmd == "maxdepth")
        else if (cmd == "output")
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
        // TODO!!! vertnorms and trinorms

        // specifying the transformations
        else if (cmd == "translate") 
            curtf = curtf * Transform::inTranslate(ss);
        else if (cmd == "rotate") 
            curtf = curtf * Transform::inRotate(ss);
        else if (cmd == "scale") 
            curtf = curtf * Transform::inScale(ss);
        
        // push/pop Transform
        else if (cmd == "pushTransform"){
            tfStack.push(Transform(curtf));
            curtf = tfStack.top();
        }
        else if (cmd == "popTransform"){
            if (tfStack.size() == 1){
                cerr<<"can't pop when transformStack is empty\n";
                continue;
            }
            tfStack.pop();
            curtf = tfStack.top();
        }

        // lighting
        else if (cmd == "directional")
        else if (cmd == "point")
        else if (cmd == "attenuation")

        // material
        else if (cmd == "diffuse") ss >> svar.diffuse;
        else if (cmd == "specular") ss >> svar.specular;
        else if (cmd == "shininess") ss >> svar.shininess;
        else if (cmd == "emission") ss >> svar.emission;   
        // yea in this assignment this is an per object variable
        else if (cmd == "ambient") ss >> svar.ambient; 


        else cerr<<"unrecognized command: "<<cmd<<endl;
    }


    return scene;
}
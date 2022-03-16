#include <iostream>
using namespace std;

// class P{
// public:
//     int x, y;
//     int mat[3];
//     P(int xx, int yy){
//         x = xx; y = yy;
//         for (int i=0; i<3; i++)
//             mat[i] = i;
//     }
// };

// P f(int xx, int yy){
//     return P(xx, yy);
// }

// int* ff(){
//     // int hi[3] = {2, 1, 0};
//     int* hi = new int(3);
//     for (int i=0; i<3; i++)
//         hi[i] = 3-i;
//     return hi;
// }

int main(){
    // P p = f(1, 3);
    // printf("%d %d\n", p.x, p.y);
    // for (int i=0; i<3; i++)
    //     cout<<p.mat[i]<<" ";
    // cout<<endl;

    // int* yo = ff();
    // for (int i=0; i<3; i++)
    //     cout<<yo[i]<<" ";
    // cout<<endl;

    float a, b;
    cin>>a>>b;
    float c = a/b;

    if (c == +inf)
        cout<<"hi\n";

    cout<<c<<endl;

    return 0;
}
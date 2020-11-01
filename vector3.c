#include "vector3.h"
#include <stdio.h>

v3 v3New(float x, float y, float z){v3 temp; temp.x=x; temp.y=y; temp.z=z; return temp;}

v3 v3Sum(v3 a, v3 b){return v3New(a.x+b.x, a.y+b.y, a.z+b.z);} //returns new vector sum
v3 v3Subs(v3 a, v3 b){return v3New(a.x-b.x, a.y-b.y, a.z-b.z);} //returns new vector substraction
v3 v3Scalar(v3 a, float n){return v3New(a.x*n, a.y*n, a.z*n);} // returns new vector product
v3 v3Prod(v3 a, v3 b){return v3New(a.x*b.x, a.y*b.y, a.z*b.z);} // returns new vector xprod

v3 v3x(){return v3New(1,0,0);}
v3 v3y(){return v3New(0,1,0);}
v3 v3z(){return v3New(0,0,1);}

void v3Print(v3 v){printf("x: %f, y: %f, z: %f\n",v.x, v.y, v.z);}
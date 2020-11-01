#ifndef VECTOR3_H_INCLUDED
#define VECTOR3_H_INCLUDED

typedef struct _v3{
    float x;
    float y;
    float z;
} v3;

v3 v3New(float x, float y, float z);
v3 v3Sum(v3 a, v3 b);
v3 v3Subs(v3 a, v3 b);
v3 v3Scalar(v3 a, float n);
v3 v3Prod(v3 a, v3 b);

v3 v3x();
v3 v3y();
v3 v3z();

void v3Print(v3 v);

#endif
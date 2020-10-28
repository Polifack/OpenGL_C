#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include "vector3.h"
#include "glaux.h"

typedef struct _transform{
    v3 position;            // v3 position in 3d space
    v3 scale;               // v3 that indicates the scaling in each angle
    v3 eulerAngles;         // v3 that indicates the rotation in each angle
} transform;


transform newTransform(v3 p, v3 s, v3 r);
void applyTransform(transform t);
transform doRotation(transform t, v3 deltaRotation);
transform doTranslation(transform t, v3 deltaPosition);
transform doScaling(transform t, v3 deltaScale);

#endif